Goals:

-   Make simple GET/POST HTTPS requests. We may POST sensitive data, so using SSL is important.
-   Smallest bundle size possible.
-   Keep all the config in cmake

Target:

-   MacOS and Windows
-   Apps that will only ever send a few HTTPS requests

Currently a release build produces a ~312kb executable. On macos you will double that size if you target arm64 & x86_64.

If change any settings and produce a smaller bundle, please let me know!
