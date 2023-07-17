%读一个文件夹中的多个wav文件，然后拼接在一起

folder = 'E:/wecsb/';

files = dir([folder '*.wav']);%读取文件夹下的所有wav文件

%files = dir(folder);

%length(files)

for i=1:length(files)

file = [folder files(i).name];

    try
   
     [Y,Fs,bits] = audioread(file);%返回值分别为Y读取片段，Fs采样率默认为44100，bits编码位数一般为16位

    catch
      
  warning(['读取文件 ' file ' 出错，可能不支持该文件格式。']);

    end
   
 try
     
   sec1=10;
     
   sec2=15;
      
  sec3=20;
      
  sec4=25;    
    
    %addPoint=2*Fs;
   
     Y_cut1=Y(((Fs*sec1+1):Fs*sec2),:); %数组的形式读取
 
       Y_cut2=Y(((Fs*sec3+1):Fs*sec4),:);
    
    Y_cutall=[Y_cut1;Y_cut2];%数组的形式拼接主要是列拼接
    
    audiowrite(Y_cutall,Fs,bits,['E:/wecsb/' 'newname' num2str(i) '.wav']);


    catch
        
warning(['写出文件 ' file ' 出错，写出地址错误。']);
  
  end

end
