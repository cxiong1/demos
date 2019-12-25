function [pano] = MyPanorama()

%% YOUR CODE HERE.
% Must load images from ../Images/Input/
% Must return the finished panorama.
img1 = imread('../input/1.jpg');
img2 = imread('../input/2.jpg');
% img1 = imread('../test_images/1.jpg');
% img2 = imread('../test_images/2.jpg');
% img1 = imread('../p2_test_images/test1/4.jpg');
% img2 = imread('../p2_test_images/test1/canvas.jpg');
% img1 = imread('../Images/Set3/canvas123.jpg');
% img2 = imread('../Images/Set3/4.jpg');
thresh = .15;

% img2 = imread('../test_images/3.jpg');
% img1 = newcan;
img1 = rgb2gray(img1);
img2 = rgb2gray(img2);
cor1 = cornermetric(img1);
cor2 = cornermetric(img2);
max1 = imregionalmax(cor1);
max2 = imregionalmax(cor2);

%Getting all the pixels that have a corner score
[row col] = size(max1);
[row2, col2] = size(max2);
Nbest = [];
Nbest2 = [];
for i = 1:row
    for j = 1:col
        if max1(i,j) == 1;
           Nbest = [Nbest; cor1(i, j) j i];
        end
    end
end

for i = 1:row2
    for j = 1:col2
        if max2(i,j) == 1;
           Nbest2 = [Nbest2; cor2(i, j) j i];
        end
        
    end
end


%Sorting the scores and selecting the top pixels with highest corner score
Best = sortrows(Nbest,1,'descend');
Best2 = sortrows(Nbest2,1,'descend');
numcorner = 1000;
B = [];
B2 = [];
B = Best(1:numcorner,:);
B2 = Best2(1:numcorner,:);

%Ploting the corner points ontop of the original picture
A = B(:,2:3);
A2 = B2(:,2:3);
% imshow(img1);
% hold on;
% plot(A(:,1),A(:,2),'r.');
% hold off;

%Removing the pixels that are close to the edge.
i = 1;
[len blah] = size(A(:,1));
while i <= len
    if ( (A(i,1) < 21) || (A(i,2) < 21) || (col - A(i,1) < 21) || (row - A(i,2) < 21))
        A(i,:) = [];
    else
        i = i + 1;
    end
    [len blah] = size(A(:,1));
end

%Removing points for image2
i = 1;
[len blah] = size(A2(:,1));
while i <= len
    if ( (A2(i,1) < 21) || (A2(i,2) < 21) || (col2 - A2(i,1) < 21) || (row2 - A2(i,2) < 21))
        A2(i,:) = [];
    else
        i = i + 1;
    end
    [len blah] = size(A2(:,1));
end

% %Plotting points again
% imshow(img1);
% hold on;
% plot(A(:,1),A(:,2),'r.');
% hold off;
% 
% imshow(img2);
% hold on;
% plot(A2(:,1),A2(:,2),'r.');
% hold off;

k1 = findkeys(img1,A);
k2 = findkeys(img2,A2);

matched = [];

[k1_size blah] = size(k1);
[k2_size blah] = size(k2);

for i = 1:k1_size
    n1 = k1(i,:);
    
    min1 = Inf;
    min2 = Inf;
    for j = 1:k2_size
        value = sum((n1 - k2(j,:)).^2);
        
        if (value < min1)
            min1 = value;
            A2coord = j;
        end
        if (value < min2 && value ~= min1)
            min2 = value;
        end
    end
    if min1/min2 < thresh
%         disp(min1/min2)
        matched = [matched; A(i,:) A2(A2coord,:)];
    end
end

mp1 = matched(:,1:2);
mp2 = matched(:,3:4);

% showMatchedFeatures(img1,img2,mp1,mp2,'montage');
% figure;
tall = size(mp1,1);
H = est_homography(mp2(1:tall,1),mp2(1:tall,2),mp1(1:tall,1),mp1(1:tall,2));

% [X, Y] = apply_homography(H, mp1(:,1), mp1(:,2));
% combined = [X  Y];
% H = est_homography(mp1(1,1),mp1(1,2),mp2(1,1),mp2(1,2));
% H = transpose(H);
% tform =  projective2d(H);
% newimg = imwarp(img1, tform); 
% imshow(newimg);
% figure;
% imshow(img2);

%Finding the up_offset and left_offset, if the new image is to the 
%left or above the current image, because apply_homography would
%return a negative coordinate. So we must account for that by adding the
%offset to the canvas

%To calculate the up offset, we gotta get the y-values from the top right
%and top left applied coordinate. We take the max(up_off_y,left_off_y) to
%determine which one would further into the negative zone.

[r,c] = size(img2);
[topLeftX,topLeftY] = apply_homography(H,1,1);
[topRightX,topRightY] = apply_homography(H,c,1);
[botLeftX, botLeftY] = apply_homography(H,1,r);
[botRightX, botRightY] = apply_homography(H,c,r);

left_offset = min(topLeftX,botLeftX);
up_offset = min(topLeftY,topRightY);

right_offset = max(topRightX,botRightX);
down_offset = max(botLeftY,botRightY);

if left_offset < 1
    left_offset = round(abs(left_offset));
else
    left_offset = 0;
end

if up_offset < 1
    up_offset = round(abs(up_offset));
else
    up_offset = 0;
end

if right_offset > c
    right_offset = round(right_offset - c);
else
    right_offset = 0;
end

if down_offset > r
    down_offset = round(down_offset - r);
else
    down_offset = 0;
end

canvasH = size(img1,1) + up_offset + down_offset;
canvasW = size(img1,2) + left_offset + right_offset;

% canvas = zeros(size(img1,1)*1.6,size(img1,2)*1.6,'uint8');
canvas = zeros(canvasH,canvasW,'uint8');

canvas(1+up_offset:r+up_offset,1+left_offset:c+left_offset) = img2;
% imshow(canvas);
[r,c] = size(img1);
negaH = inv(H);
for i = 1:canvasW
    for j = 1:canvasH
        [smol_x,smol_y] = apply_homography(negaH,i-left_offset,j-up_offset);
        smol_x = round(smol_x);
        smol_y = round(smol_y);
        
        if smol_x > 0 && smol_x < c
            if smol_y > 0 && smol_y < r
%                 if canvas(j,i) == 0
%                     canvas(j,i) = img1(smol_y,smol_x);
%                 else
%                     temporary = canvas(j,i);
%                     canvas(j,i) = (temporary + img1(smol_y,smol_x)) / 2;
%                 end
                    canvas(j,i) = img1(smol_y,smol_x);
            end
        end
        
    end
end
% imshow(canvas)
% imwrite(canvas,'canvas.jpg')
pano = canvas;
% bag = [];
% for i = 1:r
%     for j = 1:c
%         [X, Y] = apply_homography(H, j, i);
%         if X+left_offset > 1 && Y+up_offset > 1
%             X = round(X);
%             Y = round(Y);
% %             See if i,j were in the matched points array
% %             if it was, then record what X,Y and plot it later
%             
%             for u = 1:size(mp1,1)
%                 if mp1(u,:) == [i j]
%                     bag = [bag; X Y];
%                 end
%             end
%             
%             canvas(Y+up_offset,X+left_offset) = img1(i,j); 
%         end
%     end
% end
% imshow(canvas);
% [X, Y] = apply_homography(H, mp1(:,1), mp1(:,2));
% combined = [X  Y];
% hold on
% plot(X,Y,'ro')
% plot(mp1(:,1),mp1(:,2),'bo')
% plot(bag(:,1),bag(:,2),'g.')
% hold off


end

function [key1] = findkeys(img1,A)
[Alen blah] = size(A);
A2 = [];
patch =[];
for k = 1:Alen
    tarx = int16(A(k,1));
    tary = int16(A(k,2));
    %Getting 40x40 window/patch
%     disp(tarx);
    patch = img1(tary-20:tary+19,tarx-20:tarx+19);

    %Applying Gaussian to 40x40 patch
    g = fspecial('gaussian',9,1);
    blurred = imfilter(patch, g);   
%   imshow(patch);
%   imshow(blurred);

    %Subsample to 8x8 by dividing size by 5
    downed = blurred(1:5:end,1:5:end);

    %Turning 8x8 into 64x1
    reshaped = double(reshape(downed,[64,1]));

    %Getting mean
    mu = mean(reshaped);
    sig = std2(reshaped);

    reshaped = (reshaped - mu) / sig;
    reshaped = reshaped';
    A2 = [A2; reshaped];
end
key1 = A2;
end
