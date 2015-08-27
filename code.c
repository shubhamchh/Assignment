// Shubham Chhabra, 201230206
long int simple_l(long int *xp, long int y) 
{
    long int t = *xp + y;
    *xp = t;
    return t;
}

int main() 
{
    long int a = 5;
    long int c = simple_l(&a, 12L);
    return 0;
}
