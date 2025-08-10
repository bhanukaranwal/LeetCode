import java.util.*;

class MyCalendarThree {
    private TreeMap<Integer, Integer> timeline;
    private int maxBooking;

    public MyCalendarThree() {
        timeline = new TreeMap<>();
        maxBooking = 0;
    }
    
    public int book(int startTime, int endTime) {
        timeline.put(startTime, timeline.getOrDefault(startTime, 0) + 1);
        timeline.put(endTime, timeline.getOrDefault(endTime, 0) - 1);
        
        int active = 0;
        for (int delta : timeline.values()) {
            active += delta;
            maxBooking = Math.max(maxBooking, active);
        }
        return maxBooking;
    }
}
