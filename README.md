# Caeser-Cypher-and-Crypto-Analysis
### Caeser Cypher
The main idea of doing Caeser Cypher is that it replaces texts that are written in English alphabetic with a customised alphabetic. The way of creating this customised alphabetic is to use a random english key word. The key word would be inserted into an empty alphabetic after removing the dupliacted characters, then the table would be filled with rest characters in order. <br />
For example we have key word 'hello', then 'h', 'e', 'l', 'o' these 4 characters would be firstly inserted into the table. The index of the inserted position is the length of the key world, which is 5. The table would now look like:<br /> 
_ _ _ _ H E L O _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ <br />
Then filling the table with the rest characters in order, starting from character right after 'O': <br />
_ _ _ _ H E L O P Q R S T U V W X Y Z _ _ _ _ _ _ _ <br />
If reaching Z, go to A: <br />
_ _ _ _ H E L O P Q R S T U V W X Y Z A B C D _ _ _ <br />
Found duplicated character 'E', skip E and start from F (same idea for H, L, O): <br /> 
J K M N H E L O P Q R S T U V W X Y Z A B C D F G I <br />
<br />
In English we have alphabetic: <br />
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z <br />
but now we have customised alphabetic: <br />
J K M N H E L O P Q R S T U V W X Y Z A B C D F G I <br />
So if we use this customised alphabetic to do encryption, encrypting "bingo", it will become "kpulv".<br />
Doing decryption is the same idea.
### Crypto Analysis
To decrypt a cipher text which is encrypted by multiple customised alphabetic, we need to do crypto-analysis on the cipher text. <br />
Firstly we need to split the cipher text into multiple subtexts depending on the length of the key. In this project, the key lengeh is given, so that the cipher text is splited into 4 different subtext. The way of split the text is like: <br />
key length:  1 2 3 4 1 2 3 4 1 2 3 4 <br />
cipher text: A B C D E F G H I J K L <br />
subtext1: AEI <br />
subtext2: BFJ <br />
subtext3: CGK <br />
subtext4: DHL <br />
Splitting the text in this way makes sure that each subtext is encrypted by one single alphabetic. And then we can apply frequency analysis respective for each of the subtexts. Frequency order for english charatcers are: <br />
E T A O N R I S H D L F C M U G Y P W B V K J X Q Z <br />
Indicating that E is the character which is being used most in English and Z is the least use character. By using this feature, we can say the most frequently use character in the cipher text can be decrypted to character E in English, and we can apply this concept to the rest of the characters. 
