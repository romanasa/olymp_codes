import java.io.*;
import java.util.*;

public class TestGen {
    int testCount, subtaskCount;
    PrintWriter testsDesc;
    Random random = new Random(0xDEAD);
    public static int MX_N = 100000;
    public static int ALPHABET = 26;

    private static final int[] LIMITS = new int[] {10, 100, 2000, MX_N};

    public void write(String s, String folder, String subtask, int points, String comment) throws IOException {
        if (s.length() == 0)
            throw new RuntimeException("Empty string!");
        if (s.length() > LIMITS[subtaskCount])
            throw new RuntimeException("Too long string in subtask = " + subtask + " in test = " + testCount);

        String path = String.format("../%s/%02d", folder, ++testCount);
        PrintWriter out = new PrintWriter(path);
        out.println(s);
        out.close();
        testsDesc.println(String.format("%s, folder=%s, subtask=%s, points=%d, comment=\"%s\"", path, folder, subtask, points, comment));
        System.out.println(String.format("Test %d is generated", testCount));
    }

    public String reverse(String s) {
        return new StringBuilder(s).reverse().toString();
    }

    public String repeat(String cycle, int len) {
        if (cycle.length() == 0)
            throw new RuntimeException("length equal zero!");
        StringBuilder ret = new StringBuilder();
        while (ret.length() < len)
            ret.append(cycle);
        return ret.toString().substring(0, len);
    }

    public char randChar(int alphabet) {
        return (char)(random.nextInt(alphabet) + 'a');
    }

    public String genTueMorsaString(int n) {
        StringBuilder ret = new StringBuilder("a");
        while (ret.length() < n) {
            StringBuilder part2 = new StringBuilder();
            for (int i = 0; i < ret.length(); ++i)
                if (ret.charAt(i) == 'a') part2.append('b');
                else part2.append('a');
            ret.append(part2);
        }
        return ret.toString().substring(0, n);
    }

    public String genCyclicString(int n, int cycleLen, int alphabet) {
        StringBuilder cycleStr = new StringBuilder();
        for (int i = 0; i < cycleLen; ++i)
            cycleStr.append(randChar(alphabet));
        return repeat(cycleStr.toString(), n);
    }

    public String genCyclicString(int n, int alphabet) {
        int cycleLen = random.nextInt(n / 2 + 1) + 1;
        return genCyclicString(n, cycleLen, alphabet);
    }

    public String genRandomString(int n, int alphabet) {
        if (alphabet > ALPHABET)
            throw new RuntimeException("too large alphabet!");
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < n; ++i)
            str.append(randChar(alphabet));
        return str.toString();
    }

    public String genWithManyEqualCyclicSubstrings(int n, int substrings, int alphabet) {
        if (substrings <= 0)
            throw new RuntimeException("substrings = " + substrings);
        StringBuilder ret = new StringBuilder();
        ArrayList <String> subs = new ArrayList<String>();
        for (int i = 0; i < substrings; ++i) {
            int len = Math.max(1, n / 100) + 1;
            subs.add(genCyclicString(len, alphabet));
        }
        while (ret.length() < n) {
            int index = random.nextInt(substrings);
            ret.append(subs.get(index));
        }
        return ret.toString().substring(0, n);
    }

    public String insertBadSymbols(String s, int count) {
        StringBuilder builder = new StringBuilder(s);
        for (int i = 0; i < count; ++i) {
            char rnd = randChar(ALPHABET);
            int x = random.nextInt(s.length());
            builder.setCharAt(x, rnd);
        }
        return builder.toString();
    }

    public String genPalindromicString(int n) {
        StringBuilder ret = new StringBuilder();
        ArrayList <String> alphabetStrings = new ArrayList<String>();
        int alsz = random.nextInt(100) + 1;
        for (int i = 0; i < alsz; ++i) {
            int lenAlphabeticPal = random.nextInt(10) + 1;
            alphabetStrings.add(genCyclicString(lenAlphabeticPal, ALPHABET));
        }
        while (ret.length() < n) {
            int len = random.nextInt(100) + 1;
            StringBuilder pal = new StringBuilder();
            for (int i = 0; i < len; ++i)
                pal.append(alphabetStrings.get(random.nextInt(alsz)));
            if (random.nextBoolean())
                ret.append(pal.toString() + randChar(ALPHABET) + reverse(pal.toString()));
            else
                ret.append(pal.toString() + reverse(pal.toString()));
        }
        return ret.toString().substring(0, n);
    }

    public String cyclicShift(String s, int shift) {
        StringBuilder builder = new StringBuilder();
        for (int i = shift; i < s.length(); ++i)
            builder.append(s.charAt(i));
        for (int i = 0; i < shift; ++i)
            builder.append(s.charAt(i));
        return builder.toString();
    }

    public String genWithManyCyclicSubstrings(int n, int alphabet) {
        int cnt = random.nextInt(n / 100) + 1;
        if (n <= LIMITS[1])
            cnt = random.nextInt(n / 10) + 1;
        else if (n <= LIMITS[2])
            cnt = random.nextInt(n / 20) + 1;
        StringBuilder ret = new StringBuilder();
        for (int i = 0; i < cnt && ret.length() < n; ++i) {
            int len = random.nextInt(n / 100) + 1;
            ret.append(genCyclicString(len, alphabet));
        }
        return ret.toString().substring(0, Math.min(n, ret.length()));
    }

    public String genBlackWhiteString(int white, int black) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < white; ++i) builder.append('a');
        for (int i = 0; i < black; ++i) builder.append('b');
        return builder.toString();
    }

    public String appendBadSymbols(String str, int cnt) {
        StringBuilder builder = new StringBuilder(str);
        for (int i = 0; i < cnt; ++i)
            builder.append(randChar(ALPHABET));
        return builder.toString();
    }

    public int maxPow2(int n) {
        int h = 0;
        while ((1<<h+1) <= n) ++h;
        return 1<<h;
    }

    public void genPreliminary() throws IOException {
        write("aaaa", "preliminary", "subtask0", 0, "sample1");
        write("abababb", "preliminary", "subtask0", 0, "sample2");
        testCount = 0;
    }

    public void genHandleTests(int mx, int points) throws IOException {
    }

    public void genSubtask(int mx, int points) throws IOException {
        ++subtaskCount;
        String subtask = "subtask" + Integer.toString(subtaskCount);
        int sq = (int)Math.sqrt(mx);
        int pow2 = maxPow2(mx);
        int pow2_1 = pow2 + 1;
        int pow2_2 = pow2 - 1;

        write("a", "tests", subtask, 0, "s = a");
        write("aa", "tests", subtask, 0, "s = aa");
        write("aaa", "tests", subtask, 0, "s = aaa");

        write(genTueMorsaString(mx), "tests", subtask, 0, "Tue-Morsa's string; n = " + mx);
        write(genTueMorsaString(pow2), "tests", subtask, 0, "Tue-Morsa's string; n = " + mx / 2);

        write(genCyclicString(pow2, mx / 2, ALPHABET), "tests", subtask, 0, "Cyclic string, cycle = " + mx / 2);
        write(genCyclicString(pow2_1, 2, ALPHABET), "tests", subtask, 0, "Cyclic string, cycle = " + 2);
        write(genCyclicString(mx, 2, ALPHABET), "tests", subtask, 0, "Cyclic string, cycle = " + 2);
        write(genCyclicString(pow2_2, sq, 5), "tests", subtask, 0, "Cyclic string, cycle = " + sq);
        write(genCyclicString(mx, mx / 50, ALPHABET), "tests", subtask, 0, "Cyclic string, cycle = " + mx / 50);
        write(genCyclicString(mx, 10, ALPHABET), "tests", subtask, 0, "Cyclic string, cycle = " + 10);
        write(cyclicShift(genCyclicString(mx, 50, ALPHABET), 20), "tests", subtask, 0, "Cyclic string, cycle = " + 50);
        write(insertBadSymbols(genCyclicString(mx, mx / 10, ALPHABET), 100), "tests", subtask, 0, "Cyclic string, cycle = " + mx / 10 + " with bad symbols = 100");
        write(insertBadSymbols(genCyclicString(mx, 10, ALPHABET), 1000), "tests", subtask, 0, "Cyclic string, cycle = " + 10 + " with bad symbols = 1000");

        write(genWithManyEqualCyclicSubstrings(pow2, 2, ALPHABET), "tests", subtask, 0, "String with many equals substring, substring =  " + 2);
        write(genWithManyEqualCyclicSubstrings(pow2_1, 10, ALPHABET), "tests", subtask, 0, "String with many equals substring, substring =  " + 10);
        write(genWithManyEqualCyclicSubstrings(pow2_2, sq, ALPHABET), "tests", subtask, 0, "String with many equals substring, substring =  " + sq);
        write(genWithManyEqualCyclicSubstrings(mx, 5, 3), "tests", subtask, 0, "String with many equals substring, substring =  " + 5 + " with alphabet = 3");
        write(insertBadSymbols(genWithManyEqualCyclicSubstrings(mx, 5, 3), 100), "tests", subtask, 0, "String with many equals substring, substring =  " + 5 + " with alphabet = 3 and bad symbols = " + 100);

        write(genWithManyCyclicSubstrings(mx, 2), "tests", subtask, 0, "String with many cyclic substrings, alphabet = 2");
        write(genWithManyCyclicSubstrings(mx, 3), "tests", subtask, 0, "String with many cyclic substrings, alphabet = 3");
        write(genWithManyCyclicSubstrings(mx, ALPHABET), "tests", subtask, 0, "String with many cyclic substrings, alphabet = " + ALPHABET);
        write(insertBadSymbols(genWithManyCyclicSubstrings(mx, 2), mx / 100), "tests", subtask, 0, "String with many cyclic substrings, alphabet = " + ALPHABET + " with bad symbols = " + mx / 100);

        write(genPalindromicString(mx), "tests", subtask, 0, "Palindromic string");
        write(genPalindromicString(pow2_1), "tests", subtask, 0, "Palindromic string");
        write(genPalindromicString(pow2), "tests", subtask, 0, "Palindromic string");

        write(genRandomString(mx, ALPHABET), "tests", subtask, 0, "Random string with alphabet = " + ALPHABET);
        write(genRandomString(mx, 2), "tests", subtask, 0, "Random string with alphabet = " + 2);
        write(genRandomString(mx, 1), "tests", subtask, 0, "Random string with alphabet = " + 1);
        write(appendBadSymbols(genRandomString(mx - 1, 1), 1), "tests", subtask, 0, "Random string with alphabet = " + 1 + " and bad symbols in end = 1");

        write(genBlackWhiteString(mx / 2, mx / 2), "tests", subtask, 0, "Black-White string");
        write(cyclicShift(genBlackWhiteString(mx / 2, mx / 2), mx / 4), "tests", subtask, 0, "Black-White string with cyclic shift");

        testsDesc.println(String.format("comment_subtask%d=\"n &lt;= %d\"", subtaskCount, mx));
        testsDesc.println(String.format("bonus_subtask%d=%d", subtaskCount, points));
    }

    public void run() throws IOException {
        new File("../preliminary").mkdir();
        new File("../tests").mkdir();
        testsDesc = new PrintWriter("../tests.desc");

        genPreliminary();
        genSubtask(LIMITS[1], 20);
        genSubtask(LIMITS[2], 30);
        genSubtask(LIMITS[3], 50);

        testsDesc.close();
    }

    public static void main(String[] args) throws IOException {
        new TestGen().run();
    }
}
