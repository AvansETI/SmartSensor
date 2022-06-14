import cv2
import numpy as np
from matplotlib import pyplot as plt

CAPTURE_DELAY_MS = 10_000

ITERATIONS = 5
ITERATION_DELAY_MS = 1000

cap = cv2.VideoCapture(1)

#cap.set(cv2.CAP_PROP_FRAME_WIDTH, 192) 
#cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 108)

previous_frame = None    


while True:
    frames = []
    
    for i in range(ITERATIONS):
        ret, frame = cap.read()
  
        prepared_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        prepared_frame = cv2.GaussianBlur(src=prepared_frame, ksize=(5, 5), sigmaX=0)
        frames.append(prepared_frame)

        print("Captured frame:", i)
        cv2.waitKey(ITERATION_DELAY_MS)
               
    # calculate difference and update previous frame
    diff_frame0_1 = cv2.absdiff(src1=frames[0], src2=frames[1])
    diff_frame1_2 = cv2.absdiff(src1=frames[1], src2=frames[2])
    diff_frame2_3 = cv2.absdiff(src1=frames[2], src2=frames[3])
    diff_frame3_4 = cv2.absdiff(src1=frames[3], src2=frames[4])

    # we imagine the matrix is overflow/saturation protected
    diff_full = diff_frame0_1 + diff_frame1_2 + diff_frame2_3 + diff_frame3_4 

    cv2.imshow('diff_frame0_1', diff_frame0_1)
    cv2.imshow('diff_frame1_2', diff_frame1_2)
    cv2.imshow('diff_frame2_3', diff_frame2_3)
    cv2.imshow('diff_frame3_4', diff_frame3_4)

    cv2.imshow('diff_full', diff_full)

    # 4. Dilute the image a bit to make differences more seeable; more suitable for contour detection
    #diff_frame = cv2.dilate(diff_frame, np.ones((5, 5)), 1)
    # diff_frame = cv2.erode(diff_frame, np.ones((30, 30)), 1)
    # diff_frame = cv2.morphologyEx(diff_frame, cv2.MORPH_CLOSE, kernel)

    # 5. Only take different areas that are different enough (>20 / 255)
    #thresh_frame = cv2.threshold(src=diff_frame, thresh=20, maxval=255, type=cv2.THRESH_BINARY)[1]

    # 6a. Find and draw contours
    #contours, _ = cv2.findContours(image=thresh_frame, mode=cv2.RETR_EXTERNAL, method=cv2.CHAIN_APPROX_SIMPLE)
    #cv2.drawContours(image=frame, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)

    # 6b. Find and draw rectangles
    #for contour in contours:
    #  if cv2.contourArea(contour) < 50:
    #    # too small: skip!
    #      continue
    #  (x, y, w, h) = cv2.boundingRect(contour)
    #  cv2.rectangle(img=frame, pt1=(x, y), pt2=(x + w, y + h), color=(0, 255, 0), thickness=2)

    #cv2.imshow('thresh_frame', thresh_frame)
    #cv2.imshow('diff_frame', diff_frame)
    #cv2.imshow('Motion detector', frame)

# press escape to exit
    if (cv2.waitKey(CAPTURE_DELAY_MS) == 27):
      break

cap.release()
cv2.destroyAllWindows()