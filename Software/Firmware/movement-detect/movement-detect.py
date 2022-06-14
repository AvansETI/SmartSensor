import cv2
import numpy as np
from matplotlib import pyplot as plt

CAPTURE_DELAY_MS = 10_000

ITERATIONS = 5
ITERATION_DELAY_MS = 500

cap = cv2.VideoCapture(1)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920) 
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

previous_frame = None

# while True:

    # frames = []
    # 
    # for i in range(ITERATIONS):
    #     frames.append(cap.read())
    #     print("Captured frame:", i)
    # 
    #     cv2.waitKey(ITERATION_DELAY_MS)
    # 
    # print(frames)
    # 
    # if (cv2.waitKey(CAPTURE_DELAY_MS) == 27):
    #     break

while True:
    ret, frame = cap.read()
    
    # 2. Prepare image; grayscale and blur
    prepared_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    prepared_frame = cv2.GaussianBlur(src=prepared_frame, ksize=(5, 5), sigmaX=0)

    # 2. Calculate the difference
    if (previous_frame is None):
      # First frame; there is no previous one yet
      previous_frame = prepared_frame
      continue
    
    # 3. Set previous frame and continue if there is None
    if (previous_frame is None):
      # First frame; there is no previous one yet
      previous_frame = prepared_frame
      continue
    
    # calculate difference and update previous frame
    diff_frame = cv2.absdiff(src1=previous_frame, src2=prepared_frame)
    previous_frame = prepared_frame

    # 4. Dilute the image a bit to make differences more seeable; more suitable for contour detection
    diff_frame = cv2.dilate(diff_frame, np.ones((5, 5)), 1)
    # diff_frame = cv2.erode(diff_frame, np.ones((30, 30)), 1)
    # diff_frame = cv2.morphologyEx(diff_frame, cv2.MORPH_CLOSE, kernel)

    # 5. Only take different areas that are different enough (>20 / 255)
    thresh_frame = cv2.threshold(src=diff_frame, thresh=20, maxval=255, type=cv2.THRESH_BINARY)[1]

    # 6a. Find and draw contours
    contours, _ = cv2.findContours(image=thresh_frame, mode=cv2.RETR_EXTERNAL, method=cv2.CHAIN_APPROX_SIMPLE)
    
    cv2.drawContours(image=frame, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)
    # 6b. Find and draw rectangles
    # for contour in contours:
    #   if cv2.contourArea(contour) < 50:
    #     # too small: skip!
    #       continue
    #   (x, y, w, h) = cv2.boundingRect(contour)
    #   cv2.rectangle(img=img_rgb, pt1=(x, y), pt2=(x + w, y + h), color=(0, 255, 0), thickness=2)

    cv2.imshow('thresh_frame', thresh_frame)
    cv2.imshow('diff_frame', diff_frame)
    cv2.imshow('Motion detector', frame)


    cv2.waitKey(1000)

# press escape to exit
    if (cv2.waitKey(30) == 27):
        break

cap.release()
cv2.destroyAllWindows()