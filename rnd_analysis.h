
#include <iostream>
using namespace std;

class rnd_a {
  //char myName[10];
  public: 
  int nums, numx;
  double sum1, sum2, var, sd, mean, c2, var2, c22, c222;
  double m1, m2, m3, s1, s2, s3, m2n, xn_1, xn, xn_1bar, xnbar;
  double m2n_1, var3;
  double rnds[1000000];
//, sum2, sum3;

  void init();
  void get_sample(double n);
  void get_sample_online(double n);
  void print_nums();
  void print_res();
  void analyze_rnds();
};

void rnd_a::init()
{
  nums = 0;
  numx = 0;
  sum1 = 0;
  sum2 = 0;
  s1 = 0;
  s2 = 0;
  s3 = 0;
  m2n = 0;
  m2n_1 = 0;
  xn_1 = 0;
  xn = 0;
  xn_1bar = 0;
  xnbar = 0;
  mean = 0;
  var = 0;
  var2 = 0;
  m1 = 0;
  m2 = 0;
  m3 = 0;
  c2 = 0;
  c22 = 0;
  c222 = 0;
  var3 = 0;
  

}

void rnd_a::get_sample(double n)
{
  //cout << "got " << n << endl;
  rnds[nums] = n;
  nums++;
  s1 = s1 + n;
  s2 = s2 + n*n;
  s3 = s3 + n*n*n;
}

void rnd_a::get_sample_online(double n)
{
  numx++;  
  
  xnbar = xn_1bar + (n - xn_1bar)/numx;
  m2n = m2n_1 + (n-xnbar)*(n-xn_1bar);
  var3 = m2n/numx;
  c222 = var3/(xnbar*xnbar);
  m2n_1 = m2n;
  xn_1bar = xnbar;
  //cout << n << endl; 
  //cout << xn_1bar << endl;
  //cout << xnbar << endl;
  //cout << numx << endl;
}

void rnd_a::print_nums()
{
  cout << "test" << nums << endl;
  //cout << this->myName << endl;
}

void rnd_a::print_res()
{

  cout << "nums = " << numx << endl;
  cout << "sum " << sum1 << endl;
  cout << "sum^2 " << sum2 << endl;
  cout << "Mean = " << mean << endl;
  cout << "Var = " << var << endl;
  cout << "C2 = " << c2 << endl;
  cout << "s1 = " << s1 << endl;
  cout << "s2 = " << s2 << endl;
  cout << "s3 = " << s3 << endl;
  cout << "m1 = " << m1 << endl;
  cout << "m2 = " << m2 << endl;
  cout << "m3 = " << m3 << endl;
  cout << "var2 = " << var2 << endl;
  cout << "c22 = " << c22 << endl;
  cout << "numx = " << numx << endl;
  cout << "xnbar = " << xnbar << endl;
  cout << "m2n = " << m2n << endl;
  cout << "var3 = " << var3 << endl;
  cout << "c222 = " << c222 << endl;

}

void rnd_a::analyze_rnds()
{
  int i; 
  
  // mean
  for (i=0; i<nums; i++) {
    sum1 = sum1 + rnds[i];
  }
    
  mean = sum1/nums;  

  //sum of squares of differences
  for (i=0; i<nums; i++) {
    sum2 = sum2 + (rnds[i] - mean)*(rnds[i] - mean);
  }

  var = sum2/(nums-1);

  c2 = var/(mean*mean);

  m1 = s1/nums;
  m2 = s2/nums;
  m3 = s3/nums;

  var2 = m2 - m1*m1;
  c22 = var2/(m1*m1);

  

}

