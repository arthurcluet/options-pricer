//
//  BinaryTree.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

template <class T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;
public:
    void setDepth(int);
    void setNode(int, int, T);
    T getNode(int, int);
    void display();
};

template<class T>
void BinaryTree<T>::setDepth(int N) {
    _tree = {};
    for(int i = 0; i <= N; i++){
        std::vector<T> vec;
        for(int j = 0; j <= i; j++){
            T obj = T();
            vec.push_back(obj);
        }
        _tree.push_back(vec);
    }
    _depth = N;
}

template<class T>
void BinaryTree<T>::setNode(int i, int j, T element){
    _tree[i][j] = element;
}

template<class T>
T BinaryTree<T>::getNode(int i, int j){
    return _tree[i][j];
}

template<class T>
void BinaryTree<T>::display(){
    for(int i = 0; i <= _depth; i++){
        for(int j = 0; j <= i; j++){
            std::cout << _tree[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


#endif /* BinaryTree_hpp */
