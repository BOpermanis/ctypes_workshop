import numpy as np
import cv2


def load_and_prepare_map(path):
    img = cv2.imread(path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

    ret, gray = cv2.threshold(gray, 20, 255, cv2.THRESH_BINARY)
    indsx = np.where(np.min(gray, 0) == 0)[0]
    indsy = np.where(np.min(gray, 1) == 0)[0]
    xmin, ymin = np.min(indsx), np.min(indsy)
    xmax, ymax = np.max(indsx), np.max(indsy)
    gray = gray[ymin:ymax, xmin:xmax]
    img = img[ymin:ymax, xmin:xmax]
    return gray, img


if __name__ == "__main__":
    from PIL import Image
    gray, img = load_and_prepare_map("maps/maze.jpg")

    start = (10, 10)
    finish = (565, 630)

    cv2.circle(img, start, 3, (0, 255, 0), 3)
    cv2.circle(img, finish, 3, (0, 255, 0), 3)

    Image.fromarray(img).show()

