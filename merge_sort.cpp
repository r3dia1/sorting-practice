#include<iostream>
#include<vector>
using namespace std;

void Merge(vector<int>& input, int start, int middle, int end)
{
    //cout << start << " " << middle << " " << end << endl;
    vector<int> sub_1;
    vector<int> sub_2;
    sub_1.assign(input.begin()+start, input.begin()+(middle+1));
    sub_2.assign(input.begin()+(middle+1), input.begin()+(end+1));
    //cout << "sub_1 size = " << sub_1.size() << endl;
    //cout << "sub_2 size = " << sub_2.size() << endl;
    /*int i;
    for(i=0; i<sub_1.size(); i++)
        cout << sub_1[i] << " ";
    cout << endl;

    for(i=0; i<sub_2.size(); i++)
        cout << sub_2[i] << " ";
    cout << endl;*/


    int count=0;
    int index_input=start;
    int index_sub1=0;
    int index_sub2=0;
    while(count <= (end-start))
    {
        //cout << "input_index = " << index_input << endl;
        //cout << "sub1_index = " << index_sub1 << endl;
        //cout << "sub2_index = " << index_sub2 << endl;
        if(index_sub1 > (sub_1.size()-1))
        {
            input[index_input] = sub_2[index_sub2];
            index_sub2++;
            index_input++;
        }
        else if(index_sub2 > (sub_2.size()-1))
        {
            input[index_input] = sub_1[index_sub1];
            index_sub1++;
            index_input++;
        }
        else if(sub_1[index_sub1] <= sub_2[index_sub2])
        {
            input[index_input] = sub_1[index_sub1];
            index_sub1++;
            index_input++;
        }
        else
        {
            input[index_input] = sub_2[index_sub2];
            index_sub2++;
            index_input++;
        }
        
        count++;
    }
    //int i;
    /*for(i=0; i<input.size(); i++)
        cout << input[i] << " ";
    cout << endl;*/
}

void Merge_sort(vector<int>& input, int start, int end)
{
    cout << "start = " << start << " ";
    cout << "end = " << end << endl;
    if(start >= end)
        return;
    int middle = (start + end)/2;
    Merge_sort(input, start, middle);
    Merge_sort(input, middle+1, end);
    Merge(input, start, middle, end);
}

int main()
{
    vector<int> input;
    int input_number;
    char space;
    cout << "Input number sequence (eg. 11 23 63 ...): " << endl;
    while(cin >> input_number && !cin.eof())
    {
        input.push_back(input_number);
        space = cin.get();
        if(space != ' ')
            break;
    }

    Merge_sort(input, 0, input.size()-1);

    cout << "Your ordered number sequence: ";
    int i;
    for(i=0; i<input.size(); i++)
        cout << input[i] << " ";
    cout << endl;

}