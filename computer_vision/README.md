# Computer Vision

This repository contains the Panorama sSitching program. The relevant file is contained in /code/MyPanorama.m. The other files found in 
/code/ (est_homography.m, apply_homography) were provided files from the coursework. These files were not written by me.

### Program overview

The program takes input in the form of two images. As stated the program works off of a corner detection system. A corner is identified
 when the change in intensity of a pixel is drastically different from that of its neighbors. In my program, the picture is downgraded to 
 a grayscale image so that the intensity is more easily measured, as opposed to a RGB triple value vector. [r,g,b]. In a grayscale,
 a pixel has a value between 0-255. 
 
 ### Identifying a corner
 
 The shift in intensity is measured by the difference between a pixel and its neighbors. For example, the difference between 110 and 100 
 is only 10 units. You can imagine this by picturing two shades of gray, one lighter, one darker. The difference between 240 and 10 is 
 230. This can be imagined by a black pixel and white pixel. While this is a simplified overview, it highlights the basic premise of
 corner  matching.
 
 ![corner identification](https://github.com/cxiong1/demos/blob/master/computer_vision/readmeimgs/panorama_corner_identify.png)
 
 ### Matching corners.
 
 You can match a corner in one image to another corner in another image. The premise behind this process is that the surrounding pixels 
 of a corner will some what match the intensity of the neighboring pixels in the next image. You can crop out a window centering on a 
 corner and attempt to match it with all the other windows that you have identified in the next image. The pixel values might not be 
 one to one but you can select the corner with the best match. In our program, we accomplish this by taking the difference again. 
 We subtract the pixel values and we select the corner window with the lowest difference in intensity.
 
 ![corner matching](https://github.com/cxiong1/demos/blob/master/computer_vision/readmeimgs/panorama_corner_match.png)
 
 ### Estimating and Applying Homography
 
 These functions were provided in the coursework
 
 In order to determine where to overlay the picture, we need to find out where one pixel in the old image, exists in the new image. We 
 accomplish this by using a transformation matrix. We create one using the est_homography function. Because we matched the corners, 
 we have a 2-D list containing the coordinate mappings of one picture to another. By passing this into the est_homography function, it 
 returns a transformation matrix which serves as a general purpose mapping for all pixel coordinates.
 
 ### Compositing the final image
 
 In order to create the final panorama, we need to create a larger canvas, one that can hold both images overlayed ontop of each other. 
 To find the size of the larger canvas, the homography is applied to each pixel coordinate and we measure the bounds to determine how
 large the final canvas should be. The new image is directly placed ontop of the canvas while the old image is mapped using the 
 apply_homography function. The pixel intensity values are preserved.
 
 ### Final result
 
 ![final overlay](https://github.com/cxiong1/demos/blob/master/computer_vision/readmeimgs/panorama_final_overlay.png)
 
 For more examples, you can check the bottom of the **report.pdf**. It lists several images that have been stitched together using
 the above method and program and also a more indepth explanation of the process itself The separated images can be found in the /test_images/ and /train_images/ folders. The input folder serves as the input for the 
 program, i.e. the two images placed in the input folder will be stitched together.
