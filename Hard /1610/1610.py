import math

class Solution(object):
    def visiblePoints(self, points, angle, location):
        same = 0
        angles = []
        x0, y0 = location
        for x, y in points:
            if x == x0 and y == y0:
                same += 1
            else:
                ang = math.degrees(math.atan2(y - y0, x - x0))
                if ang < 0:
                    ang += 360
                angles.append(ang)
        angles.sort()
        # Duplicate the list with +360 to handle wrap-around
        angles = angles + [a + 360 for a in angles]

        max_cnt = 0
        left = 0
        for right in range(len(angles)):
            while angles[right] - angles[left] > angle:
                left += 1
            max_cnt = max(max_cnt, right - left + 1)
        return max_cnt + same
