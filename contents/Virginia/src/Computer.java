public class Computer {
    public static double computeCI(CharacteristicArray ca){
        double ci=0;
        for(int j=0;j<26;j++){
            int tmp=ca.charactristicArray[j]*(ca.charactristicArray[j]-1);
            ci=ci+tmp;
        }
        int index=ca.origin_index;
        int count=0;
        while(index<ca.cipher.length()){
            index+=ca.step;
            count++;
        }
        ci=ci/(count*(count-1));
        return ci;
    }

    public static double computeInterCI(CharacteristicArray ca1,CharacteristicArray ca2,int move){
        double inter_ci=0;
        for(int i=0;i<26;i++){
            int tem=ca1.charactristicArray[i]*ca2.charactristicArray[(i+move)%26];
            inter_ci+=tem;
        }
        inter_ci=inter_ci/(ca1.length*ca2.length);

        return inter_ci;
    }
}
