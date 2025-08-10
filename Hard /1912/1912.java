import java.util.*;

class MovieRentingSystem {
    // Key: movieId, Value: TreeSet of [price, shop]
    Map<Integer, TreeSet<int[]>> available;
    // Key: [shop, movie], Value: price
    Map<List<Integer>, Integer> priceMap;
    // TreeSet of [price, shop, movie] for all rented movies
    TreeSet<int[]> rented;

    public MovieRentingSystem(int n, int[][] entries) {
        available = new HashMap<>();
        priceMap = new HashMap<>();
        rented = new TreeSet<>((a, b) -> {
            if (a[0] != b[0]) return a[0] - b[0]; // price
            if (a[1] != b[1]) return a[1] - b[1]; // shop
            return a[2] - b[2]; // movie
        });

        for (int[] entry : entries) {
            int shop = entry[0], movie = entry[1], price = entry[2];
            available.computeIfAbsent(movie, k -> new TreeSet<>((a, b) -> {
                if (a[0] != b[0]) return a[0] - b[0]; // price
                return a[1] - b[1]; // shop
            })).add(new int[]{price, shop});
            priceMap.put(Arrays.asList(shop, movie), price);
        }
    }

    public List<Integer> search(int movie) {
        List<Integer> res = new ArrayList<>();
        if (!available.containsKey(movie)) return res;
        Iterator<int[]> it = available.get(movie).iterator();
        int cnt = 0;
        while (it.hasNext() && cnt < 5) {
            res.add(it.next()[1]);
            cnt++;
        }
        return res;
    }

    public void rent(int shop, int movie) {
        int price = priceMap.get(Arrays.asList(shop, movie));
        available.get(movie).remove(new int[]{price, shop});
        rented.add(new int[]{price, shop, movie});
    }

    public void drop(int shop, int movie) {
        int price = priceMap.get(Arrays.asList(shop, movie));
        rented.remove(new int[]{price, shop, movie});
        available.get(movie).add(new int[]{price, shop});
    }

    public List<List<Integer>> report() {
        List<List<Integer>> res = new ArrayList<>();
        Iterator<int[]> it = rented.iterator();
        int cnt = 0;
        while (it.hasNext() && cnt < 5) {
            int[] arr = it.next();
            res.add(Arrays.asList(arr[1], arr[2]));
            cnt++;
        }
        return res;
    }
}
