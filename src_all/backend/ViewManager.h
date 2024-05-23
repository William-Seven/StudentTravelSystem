#include <string>
#include <vector>
#include "View.h"

class ViewManager {
   private:
    std::vector<View> views;

   public:
    void getViews();
    void Recommendation(int obj, int quan, int mo, std::string s_s);
    void getScore(int a, int b);
    void q_sort(int left, int right);
};