cmake_minimum_required(VERSION 3.0)
project(vulpes)

aux_source_directory(src src)   
add_library(vulpes ${src})
