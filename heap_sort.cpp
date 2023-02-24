#include<iostream>
#include<vector>
using namespace std;

class binary_node{
    public:
        int data;
        binary_node* left_child;
        binary_node* right_child;
        binary_node(){
            left_child = NULL;
            right_child = NULL;
        }
};

void heapify(binary_node** ptr1){
    binary_node* temp = *ptr1;
    if((temp->right_child == NULL) && (temp->left_child == NULL))
    {
        return;
    }
    else if(temp->left_child == NULL)//只有右子情況
    {
        if(temp->data < temp->right_child->data)
        {
            int reg = temp->data;
            temp->data = temp->right_child->data;
            temp->right_child->data = reg;
            heapify(&(temp->right_child));
        }
        else
            return;
    }
    else if(temp->right_child == NULL)//只有左子情況
    {
        if(temp->data < temp->left_child->data)
        {
            int reg = temp->data;
            temp->data = temp->left_child->data;
            temp->left_child->data = reg;
            heapify(&(temp->left_child));
        }
        else
            return;
    }
    else if((temp->data < temp->right_child->data) && (temp->right_child->data > temp->left_child->data))//換右子
    {
        int reg = temp->data;
        temp->data = temp->right_child->data;
        temp->right_child->data = reg;
        heapify(&(temp->right_child));
    }
    else if((temp->data < temp->left_child->data) && (temp->right_child->data < temp->left_child->data))//換左子
    {
        int reg = temp->data;
        temp->data = temp->left_child->data;
        temp->left_child->data = reg;
        heapify(&(temp->left_child));
    }
    else
        return;
}

//由深往淺traversal (level low to high)
void build_maxHeap(binary_node** root, vector<binary_node*>& Tree, vector<int> input){
    int last_parent_index = input.size()/2 - 1; //-1 is because of the vector index
    int i;

    for(i = last_parent_index; i >= 0; i--)
    {
        binary_node* temp = Tree[i];
        heapify(&temp);
    }

}

void build_Tree(binary_node** root, vector<binary_node*>& Tree, vector<int> input){
    int total_node_num = input.size();
    int input_data;
    int tree_levelorder_index = 0;
    //cout << "total input size = " << total_node_num << endl;

    while(input.size() > 0)
    {
        input_data = input.front();
        input.erase(input.begin());

        if(*root == NULL)
        {
            //cout << "------ create root ------" << endl;
            binary_node* new_node = new binary_node;
            new_node->data = input_data;
            *root = new_node;
            Tree.push_back(new_node);
            tree_levelorder_index++;
        }
        else
        {
            //cout << "------ create child ------" << endl;
            Tree[tree_levelorder_index]->data = input_data;
            tree_levelorder_index++;
        }

        if((2*tree_levelorder_index) <= total_node_num)
        {
            binary_node* new_node = new binary_node;
            Tree[tree_levelorder_index-1]->left_child = new_node;
            Tree.push_back(new_node);
        }
        if((2*tree_levelorder_index + 1) <= total_node_num)
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

    //pointer要斷乾淨
    while(Tree.size() > 1)
    {
        size = Tree.size() - 1;
        temp = Tree[0]->data;
        //cout << "current num = " << temp << endl;
        Tree[0]->data = Tree[size]->data;
        Tree[size]->data = temp;

        del_ptr = Tree[size];//刪除last leaf & 取出
        Tree.pop_back();
        free(del_ptr);

        //最後父點pointer斷乾淨
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
        /*for(i=0; i<Tree.size(); i++)
            cout << Tree[i]->data << " ";
        cout << endl;*/

        //cout << "adjust maxHeap" << endl;
        //del_ptr = *root;
        //cout << del_ptr->data << endl;
        heapify(&(*root));
        
        /*for(i=0; i<Tree.size(); i++)
            cout << Tree[i]->data << " ";
        cout << endl;*/
    }
    sorted_number.push_back(Tree[0]->data);
    free(*root);
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
    //cout << "root value = " << root->right_child->data << endl;

    vector<int> sorted_number;
    heap_sort(sorted_number, &root, Tree);

    cout << "Your ordered number sequence: ";
    int i;
    for(i=0; i<sorted_number.size(); i++)
        cout << sorted_number[i] << " ";
    cout << endl;
    //cout << "root value = " << root->data << endl;
}