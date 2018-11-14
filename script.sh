  #!/bin/bash

  make && make clean

  echo "compiled"

  scp -fr /path/to/target robot@ev3:/path/to/destination

  echo "finished"
