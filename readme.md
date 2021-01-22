# Quick Upload

This project can be opened with PlatformIO. From there, you can build and
upload.

If you want to modify the UI, you need to install use NodeJS. Look at NodeJS
Setup

# NodeJS-less setup

If you don't want to install `npm` or `node`, then you can use the prebuilt
UI that comes with this repo, you just can't easily modify the UI.

This project can be opened in PlatformIO, and everything can be done from
there, as far as building, development and uploading.

Finally, if you have the PlatformIO CLI installed, you can use the following to build:

```
pio run
```

And you can use the following to upload

```
pio run --target upload
```

# NodeJS Setup

In order to develop on the UI, you need `nodejs`. If you only need to modify the backend/arduino, then you don't need to follow these steps. Just look at Nodeless Setup or Quick Upload.

1. Make sure you have `node` and `npm` installed. `yarn` should also fine, but
there's no `yarn.lock`, so if you run into issues, use `npm`.

1. Make sure some version of python is installed as well.

1. Make sure you're using vscode with the PlatformIO extension. Open this
directory as a project, and ensure the platformio CLI is on your path. If the
`pio` command doesn't work, then it's not installed. You likely just need to
add the following to your `~/.bashrc`:

```
export PATH=$PATH:~/.platformio/penv/bin
```

4. Run the following to setup all the node components. This only needs to be
done once the first time you setup the project (or if you change dependencies
in `package.json`).

```
npm install
```

5. Test out the setup by running the full build command:

```
npm run build
```

6. If that works, then you can run the following to upload to your device (which should be a nodemcu 12e):

```
npm run upload
```

## Front End Development

Use the following to design the UI.

```
npm start
```

The backend won't be running, so you'll have to work around that.

You can create a production build of the UI by running the following:

```
npm run web-build
```

## Back End Development

Use the following to verify that your backend compiles.

```
npm run ar-build
```

# Troubleshooting

## static_web_files.hpp not found

If you get an `static_web_files.hpp` not found error, then your UI isn't
built. Run the following to build it. You shouldn't have to do this since the
built UI is committed to the project.

```
npm run web-build
```

## package not found

You might need to install packages using one of the following commands,
depending on which build tool complains about missing packages.

```
pio lib install
```

or

```
npm install
``` 
