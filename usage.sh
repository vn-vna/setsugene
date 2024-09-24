setsugen projman create-project -n myproject

--init

--dir

--name

--description

--version

--author

--email

--license

setsugen projman project create
  --dir /path/to/project
  --name "My Project"
  --description "This is my project"
  --version 1.0.0
  --author "John Doe"
  --email ""

setsugen projman project inspect

setsugen projman asset add [PATH]
  --dest-dir [DEST_DIR]
  --dest-name [DEST_NAME]

setsugen projman asset rm [PATH]
  --force
  --recursive

setsugen projman asset ls

setsugen projman asset mv [PATH] [NEW_PATH]
  --force

setsugen projman asset inspect [PATH]

setsugen projman script create [NAME]
  --dest-dir [DEST_DIR]

setsugen projman script rm [NAME]
  --force

setsugen projman script ls

setsugen projman script mv [NAME] [NEW_NAME]
  --force

setsugen projman script inspect [NAME]

setsugen projman devenv refresh

setsugen projman devenv target add [NAME]
  --os [OS]
  --arch [ARCH]
  --compiler [COMPILER]
  --build-type [BUILD_TYPE]
  --build-dir [BUILD_DIR]

setsugen projman devenv target rm [NAME]

setsugen projman devenv target ls

setsugen projman devenv target inspect [NAME]

setsugen projman devenv target build [NAME]
  --config [CONFIG]


setsugen projman devenv init
  --env "Visual Studio 2019"

setsugen projman target add
  --os "Windows"
  --arch "x64"
  --compiler "MSVC"
  --build-type "Debug"
  --build-dir "out/build/Windows/x64/MSVC/Debug"
