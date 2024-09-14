

#ifndef TEST_RND_VARIABLE_H
#define TEST_RND_VARIABLE_H

#include <./Eigen/Eigen>
#include <./unsupported/Eigen/MatrixFunctions>

#include "ns3/random-variable-stream.h"
#include "ns3/type-id.h"
#include "ns3/object.h"
#include "ns3/attribute-helper.h"


#include "ns3/assert.h"
#include "ns3/boolean.h"
#include "ns3/double.h"
#include "ns3/integer.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/log.h"
#include "ns3/rng-stream.h"
#include "ns3/rng-seed-manager.h"
//#include "ns3/unused.h"
#include <cmath>
#include <iostream>
#include <algorithm>    // upper_bound
#include <stdint.h>

using namespace Eigen;
using namespace std;

namespace ns3 {

class ToddRandomVariable : public RandomVariableStream
{
public:
  
  /**
   * \brief Register this type.
   * \return The object TypeId.
   */
  static TypeId GetTypeId (void);

  /**
   * \brief Creates a uniform distribution RNG with the default range.
   */
  ToddRandomVariable ();

  /**
   * \brief Get the lower bound on randoms returned by GetValue(void).
   * \return The lower bound on values from GetValue(void).
   */
  double GetMin (void) const;

  /**
   * \brief Get the upper bound on values returned by GetValue(void).
   * \return The upper bound on values from GetValue(void).
   */
  double GetMax (void) const;

  /**
   * \brief Get the next random value, as a double in the specified range
   * \f$[min, max)\f$.
   *
   * \note The upper limit is excluded from the output range.
   *
   * \param [in] min Low end of the range (included).
   * \param [in] max High end of the range (excluded).
   * \return A floating point random value.
   */
  double GetValue (double min, double max);

  /**
   * \brief Get the next random value, as an unsigned integer in the
   * specified range \f$[min, max]\f$.
   *
   * \note The upper limit is included in the output range.
   *
   * \param [in] min Low end of the range.
   * \param [in] max High end of the range.
   * \return A random unsigned integer value.
   */
  uint32_t GetInteger (uint32_t min, uint32_t max);

  // Inherited from RandomVariableStream
  /**
   * \brief Get the next random value as a double drawn from the distribution.
   * \return A floating point random value.
   * \note The upper limit is excluded from the output range.
  */
  virtual double GetValue (void);
  /**
   * \brief Get the next random value as an integer drawn from the distribution.
   * \return  An integer random value.
   * \note The upper limit is included in the output range.
   */
  virtual uint32_t GetInteger (void);

  int LoadB (Matrix2d B2);


private:
  /** The lower bound on values that can be returned by this RNG stream. */
  double m_min;

  /** The upper bound on values that can be returned by this RNG stream. */
  double m_max;

  /** 1x1 Mexp */
  double B1;
  double e1;
  double p1;

  /** 2x2 MEXP */
  Matrix2d B2;
  Matrix2d e2;
  Matrix2d p2;



};  // class UniformRandomVariable



NS_LOG_COMPONENT_DEFINE ("RandomVariableStream2");

NS_OBJECT_ENSURE_REGISTERED (ToddRandomVariable);

TypeId
ToddRandomVariable::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ToddRandomVariable")
    .SetParent<RandomVariableStream>()
    .SetGroupName ("Core")
    .AddConstructor<ToddRandomVariable> ()
    .AddAttribute ("Min", "The lower bound on the values returned by this RNG stream.",
                   DoubleValue (0),
                   MakeDoubleAccessor (&ToddRandomVariable::m_min),
                   MakeDoubleChecker<double>())
    .AddAttribute ("Max", "The upper bound on the values returned by this RNG stream.",
                   DoubleValue (1.0),
                   MakeDoubleAccessor (&ToddRandomVariable::m_max),
                   MakeDoubleChecker<double>())
  ;
  return tid;
}
ToddRandomVariable::ToddRandomVariable ()
{
  // m_min and m_max are initialized after constructor by attributes
  //BB(3,3);
  NS_LOG_FUNCTION (this);
}

double
ToddRandomVariable::GetMin (void) const
{
  NS_LOG_FUNCTION (this);
  return m_min;
}
double
ToddRandomVariable::GetMax (void) const
{
  NS_LOG_FUNCTION (this);
  return m_max;
}

double
ToddRandomVariable::GetValue (double min, double max)
{
  NS_LOG_FUNCTION (this << min << max);
  double v = min + Peek ()->RandU01 () * (max - min);
  if (IsAntithetic ())
    {
      v = min + (max - v);
    }
  return v;
}
uint32_t
ToddRandomVariable::GetInteger (uint32_t min, uint32_t max)
{
  NS_LOG_FUNCTION (this << min << max);
  NS_ASSERT (min <= max);
  return static_cast<uint32_t> ( GetValue ((double) (min), (double) (max) + 1.0) );
}

double
ToddRandomVariable::GetValue (void)
{
  NS_LOG_FUNCTION (this);
  return GetValue (m_min, m_max);
}
uint32_t
ToddRandomVariable::GetInteger (void)
{
  NS_LOG_FUNCTION (this);
  return (uint32_t)GetValue (m_min, m_max + 1);
}

int ToddRandomVariable::LoadB (Matrix2d B2)
{
  
  
  cout << B2 << "test" << endl;
  return 0;
}

} //namespace ns3


//notes
// Calculate the exponential random variable.
//      double r = -mean*std::log (v);

#endif
