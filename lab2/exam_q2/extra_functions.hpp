

bool xor3(bool i1, bool i2, bool i3)
{
    return i1^i2^i3;
}

bool majority4(bool i1, bool i2, bool i3, bool i4)
{
    int sum=0;
    if(i1){
        sum+=1;
    }
    if(i2){
        sum+=1;
    }
    if(i3){
        sum+=1;
    }
    if(i4){
        sum+=1;
    }
    if(sum > 2 ) {
        return true;
    }else{
        return false;
    }
}