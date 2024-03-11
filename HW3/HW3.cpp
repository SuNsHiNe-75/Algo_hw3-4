#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cstdlib>

using namespace std;

int limit, p[1000] = { 0 }, w[1000] = { 0 }, numOfItem = 0; //Variables of dataset.

void dataLoad_c(string fd); //Load c.txt into "limit".
void dataLoad_p(string fd); //Load p.txt into "p[]".
void dataLoad_w(string fd); //Load w.txt into "w[]".
void Show_and_txtOutput(int best, int* take, int numOfItem); //Show the result on Screen and Output ans of ds1.
void Show_and_txtOutput2(int best, int* take, int numOfItem); //Show the result on Screen and Output ans of ds2.
void Show_and_txtOutput3(int best, int* take, int numOfItem); //Show the result on Screen and Output ans of ds3.
void Show_and_txtOutput4(int best, int* take, int numOfItem);
int max(int x, int y);

int main()
{
    // Readfile.
    string folder;
    cout << "Please input the dataset U wanna test: ";
    cin >> folder;
    dataLoad_p(folder);
    dataLoad_w(folder);
    dataLoad_c(folder);

    // Variables.
    int i, j;

    // 2D-Dynamic array.
    int** dp;
    dp = new int* [numOfItem + 1];
    for (i = 0; i <= numOfItem; i++)
        dp[i] = new int[limit + 1];

    // Initialize.
    for (i = 0; i < numOfItem; i++)
        for (j = 0; j <= limit; j++)
            dp[i][j] = 0;

    // Dynamic programming.
    for (i = 0; i < numOfItem; i++)
    {
        for (j = 0; j <= limit; j++)
        {
            if (j < w[i])
                dp[i + 1][j] = dp[i][j];
            else
                dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + p[i]);
        }
        //if(i>3)
           //delete[] dp[i-2];
    }
    //delete[] dp;
    //cout << "best: " << dp[numOfItem][limit] << endl;

    // Determining "take".
    int crt_dp = dp[numOfItem][limit], take[1000] = { 0 };
    int crt_item = numOfItem, crt_limit = limit;

    while (1)
    {
        if (crt_dp != dp[crt_item - 1][crt_limit])
        {
            take[crt_item - 1] = 1; // take.
            crt_dp = crt_dp - p[crt_item - 1]; // Change to the next value.
            if (crt_dp == 0)
                break;

            for (i = 0; i <= numOfItem; i++)
            {
                for (j = 0; j <= limit; j++)
                {
                    //cout << dp[i][j] << " ";
                    //cout << crt_dp << endl;
                    if (dp[i][j] == crt_dp) // Finding where "next value" at, and reset.
                    {
                        crt_item = i;
                        crt_limit = j;
                        break;
                    }
                    //cout << "crt_item: " << crt_item << endl;
                    //cout << "crt_limit: " << crt_limit << endl;
                    //system("pause");
                }
                if (dp[i][j] == crt_dp)
                    break;
            }
        }
        else
        {
            crt_dp = dp[crt_item - 1][crt_limit];
            crt_item--;
        }
    }

    // File output.
    if (folder == "ds1")
        Show_and_txtOutput(dp[numOfItem][limit], take, numOfItem);
    else if (folder == "ds2")
        Show_and_txtOutput2(dp[numOfItem][limit], take, numOfItem);
    else if (folder == "ds3")
        Show_and_txtOutput3(dp[numOfItem][limit], take, numOfItem);
    else if (folder == "ds4")
        Show_and_txtOutput4(dp[numOfItem][limit], take, numOfItem);
}

int max(int x, int y)
{
    return x > y ? x : y;
}

void dataLoad_c(string fd)
{
    fstream f;
    string path;
    path = "./dataset/" + fd + "/c.txt";
    f.open(path);
    if (!f)
        printf("Cannot open c.txt!\n");
    while (!f.eof())
        f >> limit;
    f.close();
}

void dataLoad_p(string fd)
{
    fstream f;
    string path;
    path = "./dataset/" + fd + "/p.txt";
    f.open(path);
    if (!f)
        printf("Cannot open p.txt!\n");
    while (!f.eof())
    {
        f >> p[numOfItem];
        numOfItem++;
    }
    f.close();
}

void dataLoad_w(string fd)
{
    fstream f;
    numOfItem = 0;
    string path;
    path = "./dataset/" + fd + "/w.txt";
    f.open(path);
    if (!f)
        printf("Cannot open w.txt!\n");
    while (!f.eof())
    {
        f >> w[numOfItem];
        numOfItem++;
    }
    f.close();
}

void Show_and_txtOutput(int best, int* take, int numOfItem)
{
    int i;
    fstream f;
    f.open("ans_ds1.txt", ios::out);
    f << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f << "0" << endl;
        }
    }
    f.close();
}

void Show_and_txtOutput2(int best, int* take, int numOfItem)
{
    int i;
    fstream f;
    f.open("ans_ds2.txt", ios::out);
    f << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f << "0" << endl;
        }
    }
    f.close();
}

void Show_and_txtOutput3(int best, int* take, int numOfItem)
{
    int i;
    fstream f;
    f.open("ans_ds3.txt", ios::out);
    f << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f << "0" << endl;
        }
    }
    f.close();
}

void Show_and_txtOutput4(int best, int* take, int numOfItem)
{
    int i;
    fstream f;
    f.open("ans_ds4.txt", ios::out);
    f << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f << "0" << endl;
        }
    }
    f.close();
}