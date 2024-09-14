# Supermarket Exercise

### A simple poc of a point of sale (pos) system. There are specific item rules (schemas) that are applied at checkout.

#### Interface:
```
int main() {
    {
        // Test case 1
        Pos newSystem = Pos(1);
        newSystem.scanItem("1983");
        newSystem.scanItem("4900");
        newSystem.scanItem("8873");
        newSystem.scanItem("6732");
        newSystem.scanItem("0923");
        newSystem.scanItem("1983");
        newSystem.scanItem("1983");
        newSystem.scanItem("1983");
        int total = newSystem.getTodaysTotal();
        assert(3037 == total);
    }

    // Test case 2
    {
        Pos newSystem = Pos(1);
        newSystem.scanItem("1983");
        newSystem.scanItem("4900");
        newSystem.scanItem("8873");
        newSystem.scanItem("1983");
        newSystem.scanItem("4900");
        newSystem.scanItem("8873");
        newSystem.scanItem("1983");
        newSystem.scanItem("1983");
        newSystem.scanItem("1983");
        newSystem.scanItem("6732");
        newSystem.scanItem("0923");
        int total = newSystem.getTodaysTotal();
        assert(3834 == total);
    }
 }
```
