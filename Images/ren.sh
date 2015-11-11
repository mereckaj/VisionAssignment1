i=0
for f in $(ls | sort) 
do
	mv "$f" "glue-$i.png";
	i=$(expr $i + 1);
done
