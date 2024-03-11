#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cmath>

using namespace std;

int limit, p[1000] = { 0 }, w[1000] = { 0 }, numOfItem = 0; //Variables of dataset.

void dataLoad_c(string fd); //Load c.txt into "limit".
void dataLoad_p(string fd); //Load p.txt into "p[]".
void dataLoad_w(string fd); //Load w.txt into "w[]".
void Show_and_txtOutput(int best, int* take, int numOfItem); //Show the result on Screen and Output ans of ds1.
void Show_and_txtOutput2(int best, int* take, int numOfItem); //Show the result on Screen and Output ans of ds2.
void Show_and_txtOutput3(int best, int* take, int numOfItem); //Show the result on Screen and Output ans of ds3.
void Show_and_txtOutput4(int best, int* take, int numOfItem);

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
    int i, j, k;
    int take_new[1000] = {0}, take_crt[1000] = {0}, take_best[1000] = {0};
    int E_new = 0, E_crt = 0, E_best = 0;
    float tem = 10000, threshold_tem = 3, dropRate = 0.95;
    int wei = 0;
    for(i = 0; i < numOfItem; i++)
        p[i] *= -1; // SA: Finding "min"; but we want to find "MAX".

    // Simulated Annealing.
    while(tem > threshold_tem)
    {
        // Randomly "take" some items, and finding a proper scheme.
        srand(time(NULL));
        while(1)
        {
            // Initialize.
            wei = 0;
            for(i = 0; i < numOfItem; i++)
                take_new[i] = 0;

            // Start finding.
            for(i = 0; i < numOfItem; i++)
            {
                k = rand() % (numOfItem-0+1)+0;
                take_new[k] = 1;
            }
            for(i = 0; i < numOfItem; i++)
            {
                if(take_new[i] == 1)
                    wei += w[i];
            }
            if(wei <= limit)
            {
                while(1)
                {
                    k = rand() % (numOfItem-0+1)+0;
                    if(take_new[k] != 1)
                    {
                        take_new[k] = 1;
                        wei += w[k];
                    }
                    else
                        continue;
                    if(wei > limit)
                    {
                        take_new[k] = 0;
                        wei -= w[k];
                        break;
                    }
                }
                break;
            }
                
        }

        // Calculating VALUE.
        E_new = 0;
        for(i = 0; i < numOfItem; i++)
        {
            if(take_new[i] == 1)
                E_new += p[i];
        }
        if(E_new < E_crt)
        {
            E_crt = E_new;
            for(i = 0; i < numOfItem; i++)
                take_crt[i] = take_new[i];

            if(E_new < E_best) // Record the "best SOL" while annealing.
            {
                E_best = E_new;
                for(i = 0; i < numOfItem; i++)
                    take_best[i] = take_new[i];
            }
        }
        else
        {
            //l = rand() % 2;
            //cout << "l: " << l << endl;
            if(0.5 < exp(-(E_new-E_crt)/tem))
            {
                E_crt = E_new;
                for(i = 0; i < numOfItem; i++)
                    take_crt[i] = take_new[i];
            }
            else
                for(i = 0; i < numOfItem; i++)
                    take_new[i] = take_crt[i];
        }
        tem *= dropRate;
    }
    E_best *= -1;

    // File output.
    if (folder == "ds1")
        Show_and_txtOutput(E_best, take_best, numOfItem);
    else if (folder == "ds2")
        Show_and_txtOutput2(E_best, take_best, numOfItem);
    else if (folder == "ds3")
        Show_and_txtOutput3(E_best, take_best, numOfItem);
    else if (folder == "ds4")
        Show_and_txtOutput4(E_best, take_best, numOfItem);
    else
    {
        cout << "Error!" << endl;
        return 0;
    }
}

void dataLoad_c(string fd)
{
    fstream fc;
    string path;
    path = "./dataset/" + fd + "/c.txt";
    fc.open(path);
    if (!fc)
    {
        printf("Cannot open c.txt!\n");
        return;
    }
    while (!fc.eof())
        fc >> limit;
    fc.close();
}

void dataLoad_p(string fd)
{
    fstream fp;
    string path;
    path = "./dataset/" + fd + "/p.txt";
    fp.open(path);
    if (!fp)
    {
        printf("Cannot open p.txt!\n");
        return;
    }
    while (!fp.eof())
    {
        fp >> p[numOfItem];
        numOfItem++;
    }
    fp.close();
}

void dataLoad_w(string fd)
{
    fstream fw;
    numOfItem = 0;
    string path;
    path = "./dataset/" + fd + "/w.txt";
    fw.open(path);
    if (!fw)
    {
        printf("Cannot open w.txt!\n");
        return;
    }
    while (!fw.eof())
    {
        fw >> w[numOfItem];
        numOfItem++;
    }
    fw.close();
}

void Show_and_txtOutput(int best, int* take, int numOfItem)
{
    int i;
    fstream f1;
    f1.open("ans_ds1.txt", ios::out);
    f1 << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f1 << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f1 << "0" << endl;
        }
    }
    f1.close();
}

void Show_and_txtOutput2(int best, int* take, int numOfItem)
{
    int i;
    fstream f2;
    f2.open("ans_ds2.txt", ios::out);
    f2 << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f2 << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f2 << "0" << endl;
        }
    }
    f2.close();
}

void Show_and_txtOutput3(int best, int* take, int numOfItem)
{
    int i;
    fstream f3;
    f3.open("ans_ds3.txt", ios::out);
    f3 << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        if (take[i] == 1)
        {
            cout << "1" << endl;
            f3 << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
            f3 << "0" << endl;
        }
    }
    f3.close();
}

void Show_and_txtOutput4(int best, int* take, int numOfItem)
{
    int i;
    fstream f4;
    f4.open("ans_ds4.txt", ios::out);
    f4 << best << endl;
    cout << best << endl;
    for (i = 0; i < numOfItem; i++)
    {
        cout << take[i] << " ";
        f4 << take[i] << endl;
    }
    f4.close();
}