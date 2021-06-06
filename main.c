clc
clear all
close all
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
load btBusData.noHeader.csv-001.txt_float.mat
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
NextStop=one_patch(:,1);%NextStop      : float  1076 2090 2301 1312 1041 1408 2315 1109 3141 1151 ..
LineNr=one_patch(:,2);%LineNr   : float  6 23 600 4 1 5 22 12 311 500 .
Delay=one_patch(:,4);%Delay   : float  31 254 35 25 66 162 208 47 403 199 .
LastReport=one_patch(:,5);%LastReport    : float (epoch seconds, since 1900) 1.51e+09 1.51e+09 1.51e+09 1.51e+09 ..
UnitId=one_patch(:,7);%UnitId  : float  101222 1012   14 101260 100458 101204 100461 101208 101270 101233 101252 ..
TripNr=one_patch(:,9);%TripNr  : float  41 31 20 53 98 42 29 14 27 10 ..
Latitude=one_patch(:,8);%Latitude      : float  56.2 56.2 56.2 56.3 56.2 ...
Longitude=one_patch(:,3);%Lo