
The goals of this lab are mainly to develop methods for working with
a partner in a shared repository. The context of the lab is the
example exam task given in `exam_q1` - however you are not
expected to complete the entire exam task within this lab,
as it nominally takes about 3.5 hours (some might do it faster,
some much slower).

It is worth scanning through the entire `lab1/exam_q1/readme.md`,
but you don't need to understand it in detail - the focus of
this lab are the "easy" deliverables in part A. The rest of the exercise
is something you can look at afterwards.

Our main goals for this lab are mainly around collaborating together
on a repository, and include:

- Adding a collaborator to your repository to give them access to your repo.
- Synchronising two local repos
- Working independently on two seperate parts of a repo
- Merging work that has no merge conflicts
- Working independently on the same part of a repo
- Resolving a merge conflict

Next lab we'll look at branches as a way of managing this a bit
more efficiently.

There are loads of different methodologies for managing shared development,
which map to many different commands in git. In larger projects it is
often important to maintain a very clean git history, even if it means
that the history according to git does not match the real history of
the project. As a result some people recommend methods like using
`rebase`, squashed commits, and other techniques to create a history
that is simple and manageable - this is particularly useful when the
repo history contains thousands of commits spanning many years, and
people are frequently joining and leaving the team.

However, for a project where two people are working together over
a limited time period (and communicating frequently), the easiest
way to manage things is to rely on two features: merging (today),
and branching (next week).

Tasks
=====

These tasks work best when you are genuinely working alongside someone.
However, you can actually do most of the tasks by just doing both
sides of the activity yourself - you'll still learn the same steps.

Ideally you would do these steps with a partner in lab time who is sitting
next to you, as you can communicate about what you are doing. This
partner does not have to be the same person that you do the portfolio
exercises with, nor does it have to be the same person you do the
final assessment with. However, if you want to do the exercises
later with a different partner, you can use the time to try solving
the actually exercise.

The portfolio versions of these exercises are very similar (though
with simpler code), and simply require that you demonstrate the
ability to perform the operations using git in a repository that
includes two collaborators.

Adding a collaborator to your repo
---------------------------------------

Each of you has a private lab repo called `http://github.com/ELEC40004/elec40004-2019-q4-lab-${YOUR_LOGIN}`.
At the moment only two people have access to this - you and the assessment team. In
order to collaborate with another person, and  to also to tell us who you
are working with, you should each add your chosen lab partner as a collaborator. You can do this by:

1. Go to the webpage for your github repo at `http://github.com/ELEC40004/elec40004-2019-q4-lab-${YOUR_LOGIN}`
2. Choose the "settings" tab (next to "Insights" on the top right of the page)
3. Choose "Manage access" from the options on the left side of the page.
4. Got to "invite teams or people", the green button on the bottom right of the page.
5. Type the github id of your partner into the textbox.
6. Choose the role "Write" for your partner.

Once you've done this, you should both be able to access each other's lab
repositories via the github web-page. The "Write" role means they will be
able to both push and pull to your repo.

If you want to change partners while working then you can change partners
by giving other people permissions, or remove permissions for people who
previously had it. Note that if you change partners part way though an
individual lab then you might have some more complicated merges to do.
However, changing partners between labs should be relatively simple, as
there will not be any conflicts between the different directories.


Synchronising different remote repos
---------------------------------------------

Setting up collaboration in this way means you can access each other's
repos, but synchronising via two repos is a fairly complex way of working.
It is much easier to nominate just one of your repos to be the shared
working repo. The other repo can just be left empty, or you can use
pushes to keep it synchronised if you wish.

From this point on you'll have a number of different repositories to think about:

- Lab spec repo (`spec`) : the read-only copy of the lab spec in github (where you got this text from).
- The shared working private repo (`origin`) : the private repo in github you'll both be pushing and
  pulling to/from.
- The other private repo (`mirror`) : the private repo in github from the other partner.
- Your local repo : one or more copies of the repo on your local machine
- Your partner's local repo : one or more copies of the repo on your partner's machine

It doesn't matter who's repo is chosen as `origin` and whose is `mirror`, you just
both need to agree on it.

The names in brackets are suggested as names to use as remotes for your local repo.
The name `origin` is chosen as this is the default remote name that is set up
when you clone a repository. The repository you are most likely to clone is the
shared working github repository, so `origin` is compatible with that convention.

### Setting up an empty repository with remotes

What we want to do is set up a local repository which has remotes pointing at each
of the three repos in github. We can do that by creating an empty local repository,
and then adding remotes:

1.  Create a local directory to contain your local repo, and enter that directory.

2.  Use `git init` to turn that directory into an empty git repo.

3.  Use `git remote add` to associate each of the git remotes with each of the
    repositories in github:

    a.  `spec` -> `https://github.com/ELEC40004/elec40004-2019-q4-lab.git`
    b.  `origin` -> `https://github.com/ELEC40004/elec40004-2019-q4-lab-${LOGIN1}.git`
    c.  `mirror` -> `https://github.com/ELEC40004/elec40004-2019-q4-lab-${LOGIN2}.git`

4.  Use `git remote -v` to double check that the names and github address are set up as you expect.

Whenever you perform a push and pull in your local repository, you should now think
about which repository you are pushing and pulling from.

### Pulling from the `spec` repo

By default git really wants a shared history - this means that all repos have a single
original commit, regardless of what changes or divergence happened afterwards. The
very first commit is a bit like the "identity" of the repository, which is the
same no matter how many times it is modified, pushed, pulled, or branched.
We'll use the lab spec to provide the single original history, which you can
then each modfy and diverge away from.

Pull the contents of `spec` into your local repo:
```
$ git pull spec master
```
Looking a bit more carefully at this command, the parts are:

- `git pull` : The action you want git to take.

- `spec` : The particular remote you want to pull from (which should be listed in `git remote -v`).

- `master` : The specific _branch_ on the remote you want to pull from. The master branch is
  the "default" branch, and represents the main line of development in a repo. Next week
  we'll use multiple branches, but for now there is only the master branch.

Once this happens you should have a copy of the lab spec (the same mechanism used last quarter).
If you perform `git log` you should see the first line says something like:
```
commit 1850-lots-of-hex-0492 (HEAD -> master, spec/master)
```
The parts in brackets are telling you two things:

- This particular commit is the commit you currently have checked out (`HEAD`).

- The HEAD is also at the end of the master branch.

- This commit is also at the end of the master branch in the `spec` repo.

So your checked out local copy, your local master branch, and the `spec` master branch are all synchronised and pointing at the same commit.

### Synchronising with the `origin` repo

At the moment your `origin` repo is still empty. Either you or your partner
should push to it:
```
$ git push origin master
```

Looking a bit more carefully at this command, the parts are:

- `git push` : The action you want git to take.

- `origin` : The particular remote you want to push to.

- `master` : The specific branch on the remote you want to push to. Again, this will be the default master branch.

As expected from previous experience, the lab spec should appear in the github web view for the `origin` repo.

If the person who pushed performs `git log`, then you should see that it now lists the latest commit as also being
the position of the `origin/master` branch. So now we know that four different things are
synchronised:

1. The currently checked out commit in their local repository.

2. The master branch of your local repository

3. The master branch of `spec`

4. The master branch of `origin`.

However, if the person who did not push does `git log`, it will not yet show any information
about `origin/master` - your local repository will never receive updated information
about any remote unless you explitly synchronise. If they now do `git pull`, then the
commit log should show that `origin/master` is on the same commit, and both local
repositories are fully synchronised.

At this point you can optionally push to the `mirror`, just so that both
people's private repositories are synchronised:
```
$ git push mirror master
```

Remember that the status of other repositories is not updated automatically - if
your partner independently updates `partner`, then your local repository will
not find out about it until you explicitly synchronise using `pull` (or other
commands like `fetch`).

Merging independent changes
---------------------------

The goal here is for you to be able to work in parallel with your
partner, then merge your work into one consistent repo state. In some
cases these changes will be completely independent, which is the easy case if you
can manage it.

### Creating independent changes

Each of you create a text file called `lab1/${YOUR_LOGIN}.txt` which
contains your login name (or anything else unique).

Commit this file to your local repository with an appropriate commit
message. If you each perform `git log` in your local repositories,
you'll see that things have diverged. The previous commit still exists,
and `spec/master`, `origin/master` are still
pointing at it. However, you each now have `HEAD` and `master` pointing
at a new commit. The hash for each of your commits will also be
different, because you modified the repository in different ways.

This is a key property of hashes: the hash is determined from all
properties of the commit, including the exact file contents, the
message, the date, the parent hash, and so on. Changing any property
even slightly results in a very different hash, so hashes are great
for uniquely identifying a commit. Hashes are also (almost) impossible
to forge, so given a particular hash string it would take the NSA
to come up with a set of files that would match that hash. We
sometimes use that property for assessment - if we receive or
record a hash at a particular deadline, it then _guarantees_ that the
commit it was generated from existed before that deadline. So the
actual repository can be collected later on, safe in the knowledge
it could not have been created or changed after the deadline.

### Synchronising independent changes

The two changes can now by synchronised by a sequence of
pushes and pulls:

1.  You and your partner both try to push to your changes to the `private` repo on branch `master`:
    ```
    $ git push origin master
    ```
    There is a race here - whoever does this first will succeed, and on the other
    machine it will fail.
    For the repository where it succeeded - let's call it `RepoA` - you should now find that `git log`
    shows that `origin/master` is at the latest commit alongside `HEAD` and `master`.
    The other repository (`RepoB`) will complain about not fast-forwarding, which means
    it doesn't want to skip over the intervening commit.

2.  In the local repo where the push failed (`RepoB`) you now need to now merge the changes:
    ```
    $ git pull origin master
    ```
    This will fetch the changes from `origin`, and merge them into the master
    branch on local. This results in a new "merge commit", which contains both
    sets of changes. Looking at git log, you'll see that `origin/master` still
    points at the original commit, while the local `HEAD` and `master` now
    point at the new commit.

    In the real-world, you should really test this merged commit - just because
    git thought it could merge it, the functionality of the repository might be
    slightly broken. For example, one person may have deleted a file, but the
    other person's code still relies on that file existing.

3.  Staying in the repo where the merge was just performed (`RepoB`), the changes should
    now be pushed back up to origin:
    ```
    $ git push origin master
    ```
    The local log will now show `origin/master` pointing at the merge commit.
    If you look in the github view of `origin` it will also be at the same
    commit showing both files.

4.  The other local repository (`RepoA`, where the push succeeded), does not yet have any knowledge
    of the merge commit. So the final step is to merge those changes back in:
    ```
    $ git pull origin master
    ```
    You should now see identical output from `git log` on both machines, showing that
    they now have exactly the same repository state.

This may seem like a lot of steps, but the advantage is that we have very
precise control over the complete state of the repository at every indivdual
commit. We also have a complete history of what changes were performed, what
ordered they happened in, and who changed them.

Dealing with a conflict
-----------------------

Sometimes you _have_ to edit the same file, and change some of the
same code. git will realise this when you try to merge code, and
produce a merge conflict.

### Creating a merge conflict

The exercise contains a task `A1` which requires you to modify
the file `exam_q1/lower_case.cpp`, by calling applying the function
`tolower` to each character in a file.

Both you and your partner should now implement `lower_case.cpp` independently,
in full knowledge that it will cause a conflict. In practise you would
try to avoid this by discussing who is performing each task.

You can either complete the function (it shouldn't take long), or
just return a random string if it is taking too long. Either way,
it is very likely you will end up with slightly different implementations,
which will cause a conflict.

Note that completing the task _implicitly_ requires you to create
some kind of code to test the function - you might skip this
step and hope that the implementation is fine, but to have any
confidence in it you really need the function to be compiled and have
some inputs passed through it. Any test infrastructure (source
files, test scripts) should also be checked in.

Eventually you should both have something you are happy with,
and can commit independently to your local repo.

### Resolving a merge conflict

If you follow the process for independent conflicts, you'll
find that one person can successfully push their changes,
but when the other person tries to pull their changes there
will be a "merge conflict", looking something like this:
```
$ git pull origin master
Auto-merging lab1/lower_case.cpp
CONFLICT (content): Merge conflict in lab1/lower_case.cpp
Automatic merge failed; fix conflicts and then commit the result.
```

To get a bit more information, you can use the command `git status`,
which will recap what has gone wrong:
```
$ git status
On branch master
You have unmerged paths.
(fix conflicts and run "git commit")
(use "git merge --abort" to abort the merge)

Unmerged paths:
(use "git add <file>..." to mark resolution)

both modified:   lab1/lower_case.cpp
```

If you now open `lab1/lower_case.cpp`, you'll see that
is has surrounded certain lines with arrows. So something
like:
```
<<<<<<< HEAD
string lower_case(const string &x)
{
    return "Not implemented;";
}
=======
string lower_case(const string &x)
{
    return "I didn't implement it either;";
}
>>>>>>> origin/master
```

All you need to do now is to manually modify the file so that it
looks as desired, incorporating changes from both variants as
desired. I'm afraid human intelligence is needed here,
and you will also be very grateful for any automated build and
testing scripts that you have.

Once all the conflicts have been fixed, you should commit the
repository. This commit will be a "merge commit", which means
that two slightly different git histories are being merged back
into one.

Once the merge conflict is resolved, you can push to `origin`,
then your partner can pull the merged version.

Dealing with conflicts in general
---------------------------------

These two strategies resolve most collaboration problems in small teams:

- Where possible, try to make commits that will automatically merge.

- Where necessary, manually resolve conflicts between changes.

It is worth now trying to solve some of the other exercise parts
in parallel. For example, B1, B2, and B3 can initially be performed
in parallel. However, once they are all complete you'll want to 
actually test the different components together, which may give
rise to merge conflicts.


