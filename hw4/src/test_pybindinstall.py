#!/bin/env python3
import pyexample
import pytest

#A few very simple tests to verify that pybind was installed correctly

def test_add():
    assert pyexample.add(1, 2) == 3

def test_addwithparams():
    assert pyexample.add_withparams(j=2, i=1) == 3

def test_addwithdefaults():
    assert pyexample.add_withdefaults() == 3

def test_yopla():
    assert pyexample.yopla == "yopla"

if __name__ == "__main__":
    test_add()
    test_addwithparams()
    test_addwithdefaults()
    test_yopla()
