# 1. Change the output file path by yourself 
outputfile=/Users/zhuxiaozhong/Work/LuckyCat/server/src/browser/client/ScanResource.js

# 2. Specify your resources directory name
path="../Resources"
loopDir(){

for file in find *
do
if [ -d $file ]
then
echo "$file is directory" 
cd ./$file
loopDir
cd ..

elif [ -f $file ]
then
echo "$file is file"
if [ ${file##*.} = "png" -o ${file##*.} = "jpg" ]
then
#echo "$extension"
echo "{type:\"image\", src:\"$path${PWD##*$path}/$file\"}," >> $outputfile

elif [ ${file##*.} = "plist" ]
then
echo "{type:\"plist\", src:\"$path${PWD##*$path}/$file\"}," >> $outputfile

elif [ ${file##*.} = "txt" ]
then
echo "{type:\"plist\", src:\"$path${PWD##*$path}/$file\"}," >> $outputfile

elif [ ${file##*.} = "ccbi" ]
then
echo "{type:\"ccbi\", src:\"$path${PWD##*$path}/$file\"}," >> $outputfile

elif [ ${file##*.} = "fnt" ]
then
echo "{type:\"fnt\", src:\"$path${PWD##*$path}/$file\"}," >> $outputfile

elif [ ${file##*.} = "tga" ]
then
echo "{type:\"tga\", src:\"$path${PWD##*$path}/$file\"}," >> $outputfile

elif [ ${file##*.} = "tmx" ]
then
echo "{type:\"tmx\", src:"$path${PWD##*$path}"/"$file"}," >> $outputfile

elif [ ${file##*.} = "mp3" -o ${file##*.} = "ogg" ]
then
#echo "$extension"
echo "{type:\"effect\", src:"$path${PWD##*$path}"/"$file"}," >> $outputfile
fi
fi
done
}

# Release the resource array to js file.
echo "var g_ressources = [" >> $outputfile
loopDir
#echo "{type:\"null\", src:\"null\"}" >>  $outputfile
# remove the last comma

echo "];" >> $outputfile

echo "Finish."
