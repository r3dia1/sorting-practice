#include<iostream>
#include<vector>
using namespace std;

class binary_node{
    public:
        int data; //存放數字
        binary_node* left_child; //左子ptr
        binary_node* right_child; //右子ptr
        binary_node(){
            left_child = NULL;
            right_child = NULL;
        }
};

void heapify(binary_node** ptr1){
    binary_node* temp = *ptr1;
    if((temp->right_child == NULL) && (temp->left_child == NULL))
    {
        //若recursive跑到leaf則return
        return;
    }
    else if(temp->left_child == NULL)//只有右子情況
    {
        if(temp->data < temp->right_child->data)//若是該右子較大，則和parent做swap
        {
            int reg = temp->data;
            temp->data = temp->right_child->data;
            temp->right_child->data = reg;
            heapify(&(temp->right_child));//繼續往下做heapify
        }
        else //若沒換則return
            return;
    }
    else if(temp->right_child == NULL)//只有左子情況
    {
        if(temp->data < temp->left_child->data)//若是該左子較大，則和parent做swap
        {
            int reg = temp->data;
            temp->data = temp->left_child->data;
            temp->left_child->data = reg;
            heapify(&(temp->left_child));//繼續往下做heapify
        }
        else //若沒換則return
            return;
    }
    else if((temp->data < temp->right_child->data) && (temp->right_child->data > temp->left_child->data))//換右子
    {
        //該parent擁有左右兩子樹
        //if 右子樹value > parent's value && 右子樹value > 左子樹value
        //do swap(parent, right_child)
        int reg = temp->data;
        temp->data = temp->right_child->data;
        temp->right_child->data = reg;
        heapify(&(temp->right_child));//繼續往下做heapify
    }
    else if((temp->data < temp->left_child->data) && (temp->right_child->data < temp->left_child->data))//換左子
    {
        //該parent擁有左右兩子樹
        //if 左子樹value > parent's value && 左子樹value > 右子樹value
        //do swap(parent, left_child)
        int reg = temp->data;
        temp->data = temp->left_child->data;
        temp->left_child->data = reg;
        heapify(&(temp->left_child));//繼續往下做heapify
    }
    else
        return; //其他情況則無需往下修正，所以return
}

//由深往淺traversal (level low to high)
void build_maxHeap(binary_node** root, vector<binary_node*>& Tree, vector<int> input){
    int last_parent_index = input.size()/2 - 1; //-1 is because of the vector index
    int i;

    //從最後之parent開始往level order小的node做heapify修正
    for(i = last_parent_index; i >= 0; i--)
    {
        binary_node* temp = Tree[i];
        heapify(&temp);
    }

}

//利用root指標 & node型態的vector array(Tree)去實現以BFS順序來build binary Tree
void build_Tree(binary_node** root, vector<binary_node*>& Tree, vector<int> input){
    int total_node_num = input.size(); //總node數量
    int input_data;
    int tree_levelorder_index = 0; //用來追蹤目前建樹之位置
    //cout << "total input size = " << total_node_num << endl;

    while(input.size() > 0)
    {
        //按照順序取出input
        input_data = input.front();
        input.erase(input.begin());

        if(*root == NULL)
        {
            //處裡一開始沒有Tree裡面沒有node之例外狀況
            //cout << "------ create root ------" << endl;
            binary_node* new_node = new binary_node; //先建立一個新node來當作root
            new_node->data = input_data;
            *root = new_node;
            Tree.push_back(new_node);//放入紀錄Tree node之vector array
            tree_levelorder_index++;
        }
        else
        {
            //之後則不會發生缺少node之情況，可以直接把input number寫入tree node
            //cout << "------ create child ------" << endl;
            Tree[tree_levelorder_index]->data = input_data;
            tree_levelorder_index++;
        }

        //1. 對寫入data之node，創建其左右子樹
        //2. 先確認欲創建的node，是否會超過總node數，以精準控制tree的逐步建立
        //3. 若是可以建立左/右子樹，則把它也push入紀錄Node之Tree vector array
        if((2*tree_levelorder_index) <= total_node_num) //右子樹之Level order = parent之level order*2
        {
            binary_node* new_node = new binary_node;
            Tree[tree_levelorder_index-1]->left_child = new_node;
            Tree.push_back(new_node);
        }
        if((2*tree_levelorder_index + 1) <= total_node_num) //左子樹之Level order = parent之level order*2 + 1
        {
            binary_node* new_node = new binary_node;
            Tree[tree_levelorder_index-1]->right_child = new_node;
            Tree.push_back(new_node);
        }
    }
}

void heap_sort(vector<int>& sorted_number, binary_node** root, vector<binary_node*>& Tree){
    int temp, size, parent, i;
    binary_node* del_ptr;
    //cout << "start sort" << endl;

    //依序取出MAX直到剩下最後一個node
    while(Tree.size() > 1)
    {
        size = Tree.size() - 1;
        temp = Tree[0]->data;
        //cout << "current num = " << temp << endl;

        //Swap root and last node
        Tree[0]->data = Tree[size]->data;
        Tree[size]->data = temp;

        del_ptr = Tree[size];//刪除last leaf & 取出
        Tree.pop_back();
        free(del_ptr);

        //最後父點pointer斷乾淨
        //計算最後leaf之parent的位置
        //清除該parent之左/右子點之pointer為NULL
        parent = (size+1)/2;
        //cout << "last leaf = " << size+1 << endl;
        //cout << "last parent = " << parent << endl;
        if(2*parent == (size+1))
        {
            Tree[parent-1]->left_child = NULL;
        }
        else
        {
            Tree[parent-1]->right_child = NULL;
        }

        sorted_number.push_back(temp);
        heapify(&(*root));//重新整理為MaxHeap
    }
    sorted_number.push_back(Tree[0]->data);//取出最後一個node
    free(*root);//release memory space
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

    binary_node* root = NULL;
    vector<binary_node*> Tree;

    //Build MaxHeap
    build_Tree(&root, Tree, input);
    build_maxHeap(&root, Tree, input);

    //Heap sort
    vector<int> sorted_number;
    heap_sort(sorted_number, &root, Tree);

    cout << "Your ordered number sequence: ";
    int i;
    for(i=0; i<sorted_number.size(); i++)
        cout << sorted_number[i] << " ";
    cout << endl;
}