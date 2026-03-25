#include <string>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int TEMP_RANGE  = 50 + 1; /* -10 >= && <= 40*/
constexpr int TEMP_OFFSET = 10;
constexpr int INIT_VAL    = 1000000;

#define CALIBRATION(x) x = (x + TEMP_OFFSET)
#define MINELEMENT(x) (*(min_element(x.begin(),x.end())))

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) 
{
    CALIBRATION(temperature);
    CALIBRATION(t1);
    CALIBRATION(t2);

    int answer = INIT_VAL;
    int iTimeRange = onboard.size();
    int iRecoveryDir;
    
    vector<vector<int>> vMemo(iTimeRange,vector<int>(TEMP_RANGE, INIT_VAL));
    vMemo[0][temperature] = 0;

    for (int iTime = 0 ; iTime < iTimeRange - 1 ; ++iTime)
    {
        for (int iTemp = 0 ; iTemp < TEMP_RANGE ; ++ iTemp)
        {
            if (vMemo[iTime][iTemp] == INIT_VAL) continue;

            /* Turn On */
            if (iTemp - 1 >= 0)
            {
                /* Change Temperature */
                vMemo[iTime + 1][iTemp - 1]             = min(vMemo[iTime + 1][iTemp - 1] , vMemo[iTime][iTemp] + a);
            }
            if (iTemp + 1 < TEMP_RANGE)
            {
                /* Change Temperature */
                vMemo[iTime + 1][iTemp + 1]             = min(vMemo[iTime + 1][iTemp + 1] , vMemo[iTime][iTemp] + a);
            }

            /* Keep Temperature */
            vMemo[iTime + 1][iTemp]                 = min(vMemo[iTime + 1][iTemp] , vMemo[iTime][iTemp] + b);

            /* Turn Off */
            if (iTemp > temperature) iRecoveryDir = -1;
            else if (iTemp < temperature) iRecoveryDir = 1;
            else iRecoveryDir = 0;

            if ((iTemp + iRecoveryDir) >= 0 && (iTemp + iRecoveryDir) < TEMP_RANGE)
                vMemo[iTime + 1][iTemp + iRecoveryDir]  = min(vMemo[iTime + 1][iTemp + iRecoveryDir] , vMemo[iTime][iTemp]);
        }

        if (onboard[iTime + 1])
        {
            for (int iTemp = 0 ; iTemp < TEMP_RANGE ; ++iTemp)
            {
                if (iTemp < t1 || iTemp > t2)
                    vMemo[iTime + 1][iTemp] = INIT_VAL;
            }
        }
    }

    answer = MINELEMENT(vMemo[iTimeRange-1]);
    return answer;
}

int main() 
{
    int i1 = solution(28,18,26,10,8,vector<int>{0, 0, 1, 1, 1, 1, 1}); // 40
    int i2 = solution(-10,-5,5,5,1,{0, 0, 0, 0, 0, 1, 0});  // 25
    int i3 = solution(11,8,10,10,1,{0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1});   // 20
    int i4 = solution(11,8,10,10,100,{0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1}); // 60
    return 0;
}