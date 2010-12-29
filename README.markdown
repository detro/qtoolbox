# Description

qtoolbox is a set of tools for everyday [Qt](http://qt.nokia.com) development. A "swiss army knife".
Designed to be minimalistic, does "just what promised, nothing more".

Every "tool" comes with test code, that works also as example code.

If required, tools should provide a README file written in Markdown language ([Markdown webpage](http://daringfireball.net/projects/markdown/), [on Wikipedia](http://en.wikipedia.org/wiki/Markdown)).


# Tools

## Sqlite DB Helper
Simplify Sqlite Database versioning during a project life-cycle.
It works as a Super-class for other, more specific DbHelpers.
What it "helps" to do, is to handle the versioning of the database in
a simple and clean manner: if you ask for a version of DB that is higher
then the current one, it deletes the current one and creates the new one,
before returning an open connection to the DB.

## Logging Macros
A set of logging macros. The rationale behind is to have the possibility to control all log macros (and level/verbosity)
from one file and at compile time.
Having just a release/debug mode such as qDebug() might not be enough since the more the project grows the more
clutter there is in the log file; with these macro, and a bit of housekeeping,
it is possible to decide which class is allowed to generate macros
(with no runtime check, everything is done at compile time).

## Worker Thread (TODO)
## Google Maps Widget (TODO)
## PAC file loader (TODO)


# Usage

Every tool will be sitting in a separate subdirectory.
A `".pri"` file will be provided, to make it easy to include it within your project. It's not a separate library, just a set of headers/classes.
In addition, a `"test"` subdirectory will contain a test/example application.

# Main Developers/Authors

* Luca Colantonio ([github.com/lucabox](http://github.com/lucabox))
* Ivan De Marino ([github.com/detro](http://github.com/detro))
