#include "seq_iterations.h"
#include <stdexcept>
#include <random>
#include <math.h>

using dbl = double;

/* function phi from equation x = phi(x), where phi(x) = r*x*(1 - x) */
static inline dbl phi(dbl x, dbl r)
{
   return r*x*(1 - x);
}

/* returns random point from interval (a, b) */
static dbl get_point_from_interval(dbl a, dbl b)
{
   static std::random_device rd;
   static std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(a, b);
   return dis(gen);
}

/* returns the lower point of the interval at which "good" point x0 must be */
static dbl lower_endpoint(dbl r)
{
   return (r - 1) / (2 * r);
}

/* returns the upper point of the interval at which "good" point x0 must be */
static dbl upper_endpoint(dbl r)
{
   return (r + 1) / (2 * r);
}

/* returns the x(0) from the sequnce x(n) */
static dbl get_null_point(dbl r)
{
   if (r <= 0.) throw std::runtime_error("negative constatn r is not allowed");
   dbl lp = lower_endpoint(r);
   dbl up = upper_endpoint(r);
   return get_point_from_interval(lp, up);
}

double get_next_point(double r, bool restart)
{
   static dbl x;
   if (restart)
   {
      x = get_null_point(r);
      return x;
   }
   x = phi(x, r);
   return x;
}

size_t get_amount_of_iterations(double r, int iterations_amount)
{
   if (iterations_amount!=0) return iterations_amount;

   if (r>=3)
       return 1000;
   if (r<=0.8)
       return 100;
   if (r<=1.2){
       double tmp = std::sqrt((1 -std::abs(r-1)));
       return 100 + 500*tmp;
   }
   return 100;
}

std::vector<double> get_seq_iteration_points(double r, size_t iterations)
{
   std::vector<dbl> ans;
   ans.push_back(get_next_point(r, true));
   for (size_t i = 0; i < iterations; i++){
      ans.push_back(get_next_point(r, false));
   }
   return ans;
}

std::vector<double> get_sequence_of_x_n(double r, int it, double conv){
    dbl x = get_next_point(r,true);
    std::vector<double> answer;
    dbl xN;
    size_t iter_count=0;
    do {
        iter_count++;
        xN=x;
        x=get_next_point(r,false);
        answer.push_back(xN);
    }while (std::abs(x-xN)>conv && iter_count<=get_amount_of_iterations(r,it));
    return answer;
}
