public class Decypt {
    String ciper;
    int [] key;

    public Decypt(String ciper, int[] key){
        this.ciper=ciper;
        this.key=key;
    }

    void getText(){
        for(int i=0;i<26;i++){
            StringBuffer sb=new StringBuffer("");
            for(int j=0;j< key.length;j++){
                if(i==0){
                    break;
                }
                key[j]=(key[j]+1)%26;
            }
            int index=0;
            int keyMove=0;
            while(index<ciper.length()){
                sb.append((char)(((ciper.charAt(index)-97+26-key[keyMove])%26)+97));
                index++;
                keyMove=(keyMove+1)% key.length;
            }
            System.out.println(sb);
        }
    }

}
