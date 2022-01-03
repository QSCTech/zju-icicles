  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };


class Solution {
private:
    int count = 0;
    int countb = 0;
    void printIndent(int n){
    for (int i = 0; i < n; ++i) {
        printf("    ");
    }
    }
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        printIndent(count++);
        printf("begin\n");
        if(A == NULL || B  == NULL){
            return false;
        } 
        if( A->val == B->val && helper(A->left,B->left) && helper(A->right,B->right)){
            printIndent(--count);
            printf("return true %d %d\n",A->val, B->val);
            return true;
        }
        else{
            printIndent(--count);
            printf("return %d %d\n",A->val, B->val);
            return isSubStructure(A->left,B)|| isSubStructure(A->right,B); // keep recusion
        }
    }
    bool helper(TreeNode* A,TreeNode * B){
        printIndent(countb++);
        printf("helper begin\n");
        if (B == NULL){//先判断B, 不然两个都空会先返回false.
            printIndent(--countb);
            printf("helperB == NULLend\n");
            return true;
        }
        if(A == NULL){
            printIndent(--countb);
            printf("helperA == NULLend\n");
            return false;
        }
        if (A->val == B->val){
            printIndent(--countb);
            printf("helper %d %dend\n",A->val,B->val);
            return helper(A->right,B->right) && helper(A->left,B->left);
        }
        else{
            return false;
        }
    }
};