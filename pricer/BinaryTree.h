#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>

template <class T>
class BinaryTree
{
private:
    int _depth;
    std::vector< std::vector<T> > _tree;
public:
    void setDepth(int);
    void setNode(int, int, T);
    T getNode(int, int);
    void display();
    void displayMore();
};

template<class T>
void BinaryTree<T>::setDepth(int N) {
    if (_depth == 0) {
        _tree.resize(N + 1);
        for (int i = 0; i <= N; i++) {
            std::vector<T> vec;
            for (int j = 0; j <= i; j++) {
                T obj = T();
                vec.push_back(obj);
            }
            //_tree.push_back(vec);
            _tree[i] = vec;
        }
        _depth = N;
    }
    else {
        if (N < _depth) _tree.resize(N + 1);
        else if (N > _depth) {
            for (int i = _depth + 1; i <= N; i++) {
                std::vector<T> vec;
                for (int j = 0; j <= i; j++) {
                    T obj = T();
                    vec.push_back(obj);
                }
                _tree.push_back(vec);
            }
        }
        _depth = N;
    }
}

template<class T>
void BinaryTree<T>::setNode(int i, int j, T element) {
    _tree[i][j] = element;
}

template<class T>
T BinaryTree<T>::getNode(int i, int j) {
    return _tree[i][j];
}


template<class T>
void BinaryTree<T>::displayMore() {
    int n_spaces = (_depth + 1) * 2;

    for (int i = 0; i <= _depth; i++) {
        for (int k = 0; k < n_spaces - 2 * i - 1; k++) {
            std::cout << " ";
        }

        for (int j = 0; j <= i; j++) {
            std::cout << _tree[i][j];
            if (j < i) {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;

        if (i < _depth) {
            for (int k = 0; k < n_spaces - 2 * i - 2; k++) {
                std::cout << " ";
            }

            for (int j = 0; j <= i; j++) {
                std::cout << "/ \\ ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}


template<class T>
void BinaryTree<T>::display() {
    for (int i = 0; i <= _depth; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << _tree[i][j] << " ";
        }
        std::cout << std::endl;
    }

    displayMore();
}