public class Main {

    public static void getCI(Cipher cipher,int range){
        for (int step = 1; step < range; step++) {
            System.out.print(step+" : ");

            for(int origin_index=0; origin_index < step; origin_index++){
                CharacteristicArray ca =new CharacteristicArray(cipher, step, origin_index);
                double ci=Computer.computeCI(ca);
                System.out.print(String.format("%.4f",ci)+"  ");
            }

            System.out.println();
        }
    }
    public static void getInterCI(Cipher cipher, int step){
        CharacteristicArray ca=new CharacteristicArray(cipher, step, 0);
        for(int i=1;i<step;i++){

            System.out.println(i);
            CharacteristicArray ca_tmp=new CharacteristicArray(cipher, step, i);
            for(int move=0;move<26;move++){
                double inter_ci=Computer.computeInterCI(ca, ca_tmp, move);
                System.out.print(String.format("%.3f",inter_ci)+"  ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args){
            //尝试密钥长度的范围range，这里是21
        int range=21;
        Cipher cipher=new Cipher("veadjudytrvspwnmfaiirimdbbqeiovmzbimqsfhwacituskdljqigfmvdtqjyqajcuwacuzqlczqazlkveadzacnmypmrsycmfuejhqgnzqeirlltipuakbrlqemresaxqyistrejhlszuzgxvdrfpceyihwcdzymplsvwacxaashzpubyfbqswfuaqahprfmyxlazmghyxtirhwoqbmjihrezobavifeihxpzchprvoqwoqlohqgwyzkyevxwvizwqzglowgfeuelsizfapyxcirxqfwaqgekdwrziyuifhyzluxyacxjpjyxbwhldkwoeusiobepiilsiuqqtzirefhegilprhrdwmvxzvkvwgpwhaggouckwomeibrrtmlqqsbrrnmndbypocpwhyleqfmgvnzbxvllsecxylosnqvnazihkczinubrooyeayyopszgxtmtbazhlumholjoucimfxglspmebfaiirrdymhnruilcfqzkbyqdlfieqpefhmrgigewsodrwlylwsodukuzashzpubymacarpqjofashkgzoczglszmdtxobyzgqfwjyrxcdbazykbyisrabbqqiowf");

            //计算重合指数，通过观察判断可能的密钥长度
//        getCI(cipher,range);

            //确定密钥长度step后求相对位移，这里是设第0个元素的绝对位移为0，求它和其它元素的相对位移
//        int step=9;
//        getInterCI(cipher, step);

            //确定相对定位移后，列出相对向量key，穷举26次即可，人工观察即可
//        int[] key={0,17,1,16,11,25,21,7,25};
//        Decypt d=new Decypt(cipher.cipher,key);.
//        d.getText();                    //解密


    }
}
