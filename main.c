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

Lines=unique(sort(LineNr));
maxLines=length(Lines);
maxTripsList=length(unique(sort(TripNr)));
 
tripsOfLines=zeros(maxTripsList,maxLines);
 
for kk=1:length(Lines)
    tp=find(LineNr==Lines(kk));
    Trips=unique(sort(TripNr(tp)));
    tripsOfLines(1:length(Trips),kk)=Trips;
end

ListOfPossible=[];
figure(1000),hold on
for kk=1:maxLines
    for gg=1:maxTripsList
        if tripsOfLines(gg,kk)>0
            tu=find(TripNr==tripsOfLines(gg,kk) & LineNr==Lines(kk));
 
            lat=Latitude(tu);
            lon=Longitude(tu);
            checkStaionarityOfBus=unique(lon);
            
            if (length(checkStaionarityOfBus)>20 && sum(lon==0)==0)
%                 figure,plot(lon,lat,'*'),title(['the pathway of Line= ',num2str(Lines(kk)),' and Tripr= ', num2str(tripsOfLines(gg,kk))])
                ListOfPossible=[ListOfPossible;Lines(kk),tripsOfLines(gg,kk)];
            else
%                 figure(1000),plot(lon,lat,'*')
            end
        end
    end
end

lonV=[];latV=[];delayV=[];
for kk=1:1;%83
    line1=ListOfPossible(kk,1);
    trip1=ListOfPossible(kk,2);
    tu=find(TripNr==trip1 & LineNr==line1);
    lat=Latitude(tu);
    lon=Longitude(tu);
    delay=Delay(tu);
lonV=[lonV,lon'];latV=[latV,lat'];delayV=[delayV,delay'];
end
 figure,plot(lonV,latV,'*')

lonVV=lonV;
lonVV=lonVV-min(lonVV);
lonVV=lonVV/max(lonVV);
lonVV=lonVV+0.01;
%%%%%%%%
latVV=latV;
latVV=latVV-min(latVV);
latVV=latVV/max(latVV);
latVV=latVV+0.01;
%%%%%%%%%
P=[lonVV',latVV'];
DT = delaunayTriangulation(P);
 
IC = incenter(DT);
figure,triplot(DT)
hold on
plot(IC(:,1),IC(:,2),'*r')

p.faces = DT.ConnectivityList;
p.vertices = DT.Points* 1200;
 
% rasterize it
I = patch_rasterize(p);
% I = patch_rasterize();
figure, hold on;
imagesc(I); axis image;
triplot(p.faces, p.vertices(:,1), p.vertices(:,2), 'color', 'white');