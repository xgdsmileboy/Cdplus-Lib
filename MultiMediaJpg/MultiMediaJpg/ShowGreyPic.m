
I = load('D:\Program\C++\MultiMediaJpg\MultiMediaJpg\result.txt');
I_new=mat2gray(I);%����I�����ŻҶ�ֵ�ľ���
imshow(I_new)
imwrite(I_new,'gray.jpg');
