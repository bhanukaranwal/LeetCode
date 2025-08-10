import java.util.*;

class Solution {
    public int minRefuelStops(int target, int startFuel, int[][] stations) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int n = stations.length, stops = 0, i = 0;
        long fuel = startFuel;

        while (fuel < target) {
            // Add all reachable stations' fuel to the heap
            while (i < n && stations[i][0] <= fuel) {
                maxHeap.offer(stations[i][1]);
                i++;
            }
            // If no station to refuel from, cannot reach target
            if (maxHeap.isEmpty()) return -1;
            // Refuel at the station with the most fuel
            fuel += maxHeap.poll();
            stops++;
        }
        return stops;
    }
}
