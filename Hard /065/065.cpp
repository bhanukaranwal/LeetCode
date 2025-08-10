class Solution {
public:
    bool isNumber(string s) {
        int e=0,d=0,sign=0,dot=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='.'){
                if(dot!=0) return false;
                dot=1;
                if(d==1) continue;
                if(i==s.size()-1||((s[i+1]<'0'||s[i+1]>'9'))) return false;
                continue;
            }
            if(s[i]=='+'||s[i]=='-'){
                if(d==1) return false;
                if(i==s.size()-1) return false;
                if(sign==1){
                    if(e==0) return false;
                }
                if(sign==2) return false;
                sign+=1;
                // e=1;
                continue;
            }
            if((s[i]=='e'||s[i]=='E')){
                if(e==1||d==0) return false;
                e=1;
                dot=1;
                d=0;
                if(i==s.size()-1||((s[i+1]<'0'||s[i+1]>'9')&&(s[i+1]!='+'&&s[i+1]!='-'))) return false;
                continue;
            }
            if(s[i]<'0'||s[i]>'9') return false;

            if(s[i]>='0'&&s[i]<='9'){
                d=1;
                // e=1;
            }
            else d=0;

        }
        return true;
    }
};
