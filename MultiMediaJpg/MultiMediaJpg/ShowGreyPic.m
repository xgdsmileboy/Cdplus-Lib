
I = load('D:\Program\C++\MultiMediaJpg\MultiMediaJpg\result.txt');
I_new=mat2gray(I);%其中I是你存放灰度值的矩阵
imshow(I_new)
imwrite(I_new,'gray.jpg');
