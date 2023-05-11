Goals:

-   Make simple GET/POST HTTPS requests. We may POST sensitive data, so using SSL is important.
-   Smallest bundle size possible.
-   Keep all the build config in cmake

Target:

-   MacOS and Windows
-   Apps that will only ever send a few HTTPS requests

Currently the Release build produces an executable size of ~312kb on MacOS, ~250 on Windows. On MacOS you will double that size if you target arm64 & x86_64.

If you change any settings and produce a smaller bundle, please let me know!
