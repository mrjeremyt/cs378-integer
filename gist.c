int l1 = strlen(s1);
int l2 = strlen(s2);
int i, j, k = 0, c = 0;
char *r = (char *) malloc (l1+l2);;
int temp;
 
strrev(s1);
strrev(s2);
for (i = 0;i <l1+l2; i++) {
    r[i] = 0 + '0';
}
 
for (i = 0; i <l1; i ++) {
    c = 0; k = i;
    for (j = 0; j < l2; j++) {
        temp = get_int(s1[i]) * get_int(s2[j]);
        temp = temp + c + get_int(r[k]);
        c = temp /10;
        r[k] = temp%10 + '0';
 
        k++;
    }
    if (c!=0) {
        r[k] = c + '0';
        k++;
    }
}
 
r[k] = '\0';
strrev(r);
return r;