import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while not cap.isOpened():
    cv2.waitKey(1000)
    print('.')
    

previous_frame = None

while True:
    ret, img_rgb = cap.read()

    cv2.imshow('test', img_rgb)
    prepared_frame = cv2.cvtColor(img_rgb, cv2.COLOR_RGB2GRAY)

    prepared_frame = cv2.GaussianBlur(src=prepared_frame, ksize=(5,5), sigmaX=0)

    if (previous_frame is None):
        previous_frame = prepared_frame
        continue

    diff_frame = cv2.absdiff(src1=previous_frame, src2=prepared_frame)
    previous_frame = prepared_frame

    cv2.imshow('diff', diff_frame)

    kernel_erode = np.ones((5,5))
    kernel_dilate = np.ones((10,10))

    diff_frame = cv2.erode(diff_frame, kernel_erode, 1)
    diff_frame = cv2.dilate(diff_frame, kernel_dilate, 1)

    thresh_frame = cv2.threshold(src=diff_frame, thresh=20, maxval=255, type=cv2.THRESH_BINARY)[1]

    cv2.imshow('diff_frame', diff_frame)

    contours, _ = cv2.findContours(image=thresh_frame, mode=cv2.RETR_EXTERNAL, method=cv2.CHAIN_APPROX_SIMPLE)
 
#    cv2.drawContours(image=img_rgb, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)
    for contour in contours:
        if cv2.contourArea(contour) < 50:
        # too small: skip!
            continue
        (x, y, w, h) = cv2.boundingRect(contour)
        cv2.rectangle(img=img_rgb, pt1=(x, y), pt2=(x + w, y + h), color=(0, 255, 0), thickness=2)

    cv2.imshow('Motion Detect', img_rgb)

    if (cv2.waitKey(33) == 27):
        break

cap.release()
cv2.destroyAllWindows()

