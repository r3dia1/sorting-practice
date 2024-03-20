#include<iostream>
#include<vector>
using namespace std;

void quick_sort(vector<int>& input, int start, int end)
{
    if(start >= end)
        return;
    int pivot = start;
    int left = start;
    int right = end;
    int swap;
    //int i;

    //cout << "start run" << endl;
    while(left != right)
    {
        //find element <= pivot from right
        while((input[right] > input[pivot]) && (left < right)) //avoid right pass through left
        {
            right--;
        }
        //cout << "right = " << right << endl;

        //find element > pivot from left
        while((input[left] <= input[pivot]) && (left < right)) //avoid left pass through right
        {
            left++;
        }
        //cout << "left = " << left << endl;

        if(left < right) //when left and right do not encounter do swap(left, right) 
        {
            //cout << "-----swap left right-----" << endl;
            swap = input[left];
            input[left] = input[right];
            input[right] = swap;
        }
    }

    //cout << "====swap pivot====" << endl;
    swap = input[right];
    input[right] = input[pivot];
    input[pivot] = swap;

    /*cout << "Your ordered number sequence: ";
    for(i=0; i<input.size(); i++)
        cout << input[i] << " ";
    cout << endl;*/

    // run quick_sort recursive
    quick_sort(input, start, left-1);
    quick_sort(input, left+1, end);
}

int main()
{
    vector<int> input;
    int input_number;
    char space;
    cout << "Input number sequence (eg. 11 23 63 ...): ";
    while(cin >> input_number && !cin.eof())
    {
        input.push_back(input_number);
        space = cin.get();
        if(space != ' ')
            break;
    }

    quick_sort(input, 0, input.size()-1);

    cout << "Your ordered number sequence: ";
    int i;
    for(i=0; i<input.size(); i++)
        cout << input[i] << " ";
    cout << endl;
}