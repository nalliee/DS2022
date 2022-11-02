#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <algorithm>
using namespace std;

template <typename Comparable>
class Node
{
  private:
    Comparable data;
    Node *left;
    Node *right;

  public:
    /**
     * Construct Node.
    */
    Node() {};

    /**
     * Get the _val from the node.
    */
    virtual Comparable getdata() const;

    /**
     * Assign _val to the data.
    */
    virtual void setdata(const Comparable &_val);

};

template <typename Comparable>
class BinaryTree
{
  private: 
    class BinaryTreeNode: public Node<Comparable> {};
    BinaryTreeNode *root;

  public:
    /**
     * Constructor
    */
    BinaryTree( ) : root{ nullptr } {}

    /**
     * Destructor for the tree
    */
    virtual ~BinaryTree( ) {}

    /**
     * Insert _val to the tree.
    */
    virtual void insert( const Comparable & _val ) {}

    /**
     * Inorder Traversal.
    */
    virtual void preorderT(BinaryTreeNode * & t) 
    {
      if(t != nullptr)
      {
        cout << t -> data << " ";
        preorderT(t -> left);
        preorderT(t -> right);
      }
    }

    /**
     * Preorder Traversal.
    */
    virtual void inorderT(BinaryTreeNode * & t) 
    {
      if(t != nullptr)
      {
        inorderT(t -> left);
        cout << t -> data << " ";
        inorderT(t -> right);
      }
    }

    /**
     * Postorder Traversal.
    */
    virtual void postorderT(BinaryTreeNode * & t) 
    {
      if(t != nullptr)
      {
        postorderT(t -> left);
        postorderT(t -> right);
        cout << t -> data << " ";
      }
    }

    /**
     * Remove _val from the tree
    */
    virtual void remove( const Comparable & _val ) {}

};

template <typename Comparable>
class BinarySearchTree
{
  private:
    class BinarySearchTreeNode: public Node<Comparable> {};
    BinarySearchTreeNode *root;

  public:
    /**
     * Constructor
    */
    BinarySearchTree( ) : root{ nullptr } {}

    /**
     * Destructor for the tree
     */
    virtual ~BinarySearchTree( ) {}

    /**
     * Insert _val to the tree
    */
    virtual void insert( const Comparable & _val ) {}

    /**
     * Find the smallest item in the tree
    */
    virtual const Comparable & findMin( ) const = 0

    /**
     * Find the largest item in the tree
    */
    virtual const Comparable & findMax( ) const = 0

    /**
     * Remove _val from the tree
    */
    virtual void remove( const Comparable & _val ) {}
    
};

template <typename Comparable>
class AvlTree: public BinarySearchTree<Comparable>
{
  private:
    class AvlNode: public Node<Comparable>
    {
        int height;
    };
    AvlNode *root;

  public:
    /**
     * Constructor 
    */
    AvlTree( ) : root{ nullptr } {};

    /**
     * Destructor for the tree
    */
    virtual ~AvlTree() {};

    /**
     * Insert _val to the tree
    */
    virtual void insert( const Comparable &_val ) {}

    /**
     * Rotate binary tree node
    */
    virtual void rotate( const Comparable *& t) {}

    /**
     * Balance the tree
    */
    virtual void balance( AvlNode * & t ) {}

    /**
     * Return the height of node
    */
    virtual int height( AvlNode *t ) const = 0

    /**
     * Remove _val from the tree
    */
    virtual void remove( const Comparable &_val ) {}

};

#endif