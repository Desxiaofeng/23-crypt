public class CharacteristicArray {

    int[] charactristicArray=new int[26];
    int step;
    int origin_index;
    String cipher;
    String ALPHABET="abcdefghijklmnopqrstuvwxyz";
    int length=0;

    public CharacteristicArray(Cipher cipher, int step, int origin_index){
        this.cipher =cipher.cipher;
        this.step=step;
        this.origin_index=origin_index;
        getCharacteristicArray();
        getLength();
    }

    public void getCharacteristicArray(){
        //初始化特征数组
        for(int j=0;j<26;j++){
            charactristicArray[j]=0;
        }
        //计算特征数组（即计数）
        for (int j = 0; j < 26; j++) {
            int index = origin_index;
            while (index < cipher.length()) {
                if(ALPHABET.charAt(j)== cipher.charAt(index)){
                    charactristicArray[j]++;
                }
                index+=step;
            }
        }
    }

    public void getLength(){
        int index=origin_index;
        int tmp_length=0;
        while(index< cipher.length()){
            index+=step;
            tmp_length++;
        }
        this.length=tmp_length;
    }
}
