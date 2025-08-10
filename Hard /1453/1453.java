class Solution {
    private static final double EPS = 1e-8;

    public int numPoints(int[][] darts, int r) {
        int n = darts.length;
        int result = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (double[] center : getCenters(darts[i], darts[j], r)) {
                    int count = 0;
                    for (int[] dart : darts) {
                        if (dist(center, dart) <= r + EPS) {
                            count++;
                        }
                    }
                    result = Math.max(result, count);
                }
            }
        }
        return result;
    }

    // Calculate all possible centers for a circle of radius r passing through p1 and p2
    private List<double[]> getCenters(int[] p1, int[] p2, int r) {
        List<double[]> centers = new ArrayList<>();
        double dx = p2[0] - p1[0], dy = p2[1] - p1[1];
        double d2 = dx * dx + dy * dy;
        double d = Math.sqrt(d2);
        if (d > 2 * r + EPS) return centers; // Too far apart

        double mx = (p1[0] + p2[0]) / 2.0;
        double my = (p1[1] + p2[1]) / 2.0;
        double h = Math.sqrt(r * r - (d / 2) * (d / 2));
        double ox = -dy * h / d;
        double oy = dx * h / d;

        centers.add(new double[]{mx + ox, my + oy});
        centers.add(new double[]{mx - ox, my - oy});
        return centers;
    }

    private double dist(double[] c, int[] p) {
        return Math.hypot(c[0] - p[0], c[1] - p[1]);
    }
}
