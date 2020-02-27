
Previously we looked at pushing, pulling, and merging. In order to
work in a more disciplined way, we often want to maintain multiple
branches.

So far we have only seen one branch: master. However, you can have
any number of branches, each of which represents a different stream
of development. Branches can also be pushed and pulled to and from
remotes, allowing you to synchronise different branches between
repos.

Our main goals for this lab are mainly around branches, and include:

- Creating a local branch.
- Making changes between branches.
- Merging changes from a local branch.
- Pushing to a remote branch.
- Pulling from a remote branch.
- Using feature branches to work in parallel.

Tasks
=====

If we imagine git commits as a linked data-structure, then each branch represents
a named pointer to the end of a list. At the moment we have seen a single
history along the master branch. For example, we might have made three commits
and created a history that looks like this:
```
            master
             HEAD
              :
              v
C0 <-- C1 <-- C2
```
We might then perform some commits in parallel, and use a merge to get back to
a single history. For example, here C4 represents a merge commit which
brings together two different histories:
```
                    master
                     HEAD
                      :
                      v
C0 <-- C1 <-- C2 <--- C4
              ^       |
              +--C3<--+
```
We could move HEAD around within this history using `checkout C1`, to create a
detached head:
```
                    
      HEAD          master
       :              :
       v              v
C0 <-- C1 <-- C2 <--- C4
              ^       |
              +--C3<--+

```
However, the branch `master` is the entire history pointed to by the `master`
pointer, regardless of which commit you currently have checked out.

There are two common uses for additional branches:

- Creating temporary working branches, particularly if you want to access
  code from a historical commit. Usually these are short-lived, and often
  only exist locally within a repo.

- Creating feature branches, which represent a sequence of commits needed
  to implement a test a particular feature. For a big feature these might
  last for a long time, and be shared amongst multiple repos.

The idea is to only merge back into the master branch when you have a
working repository state - any commits where the code is partially
broken should stay on a different branch until the code is fixed, or
the branch is discarded.

Creating a local branch
-----------------------

You can create a local branch when you check out a particular commit:

1.  Use `git log` to pick one of your commits from last week's lab (something older than the last commit).

2.  Check it out into a branch called `local_branch`:
    ```
    $ git checkout HASH -b local_branch
    ```

3.  You should now be on a branch called `local_branch`, with HEAD (i.e. the working directory) reflecting
    your chosen commit. You can list the local branches using `git branch`:
    ```
    $ git branch
      master
    * local_branch
    ```
    The asterisk indicates which branch you are currently on.

4.  If you use `git log`, you will now see the history of this branch, which will not
    include any commits after this point.

5.  To get back to `master`, simply use `git checkout master`, and you should see the
    whole history from `git log`.

If we assume that the original commits looked like this:
```                  
                    master
                      :
                      v
C0 <-- C1 <-- C2 <--- C4
```
and you created the branch at C1, your history now looks like this:
```
                    master
                      :
                      v
C0 <-- C1 <-- C2 <--- C4
       ^
       :
   local_branch
```

Modifying a local branch
------------------------

It is occasionally useful to modify something historical, then (carefully) merge those changes
back into master.

1.  Switch to the `local_branch` branch:
    ```
    $ git checkout local_branch
    ```

2.  Modify the state of the repository in some trivial way. For example, add a comment to
    some code, or change the instructions slightly.

3.  Commit the code as normal. This will make a commit on `local_branch`, but will not
    touch `master`.

4.  You can still switch back and forth between the two branches using `git checkout master`
    and `git checkout local_branch`.

Your branches now look something like this:
```
                    master
                      :
                      v
C0 <-- C1 <-- C2 <--- C4
       ^
       +-- C5
            ^
            :
        local_branch
```

Merging changes back in
-----------------------

We've already seen that git can merge together different commits, and
it is happy to do this for branches too. Let us merge the results back
into master.

1.  Switch to master:
    ```
    $ git checkout master
    ```

2.  Merge from `local_branch`:
    ```
    $ git merge local_branch
    ```
    At this point you may or may not have a merge conflict to resolve. You should pay
    particular attention to merges from way back in history, as git's automatic
    conflict resolution may sometimes do unexpected things. Really you want automated
    tests so that you can verify the merge has completed successfully.

3.  (If needed) Resolve merge conflicts and commit.

4.  View the changes using `git log`. You should be able to see all the expected
    commits from `master`, plus the additional commit from `local_branch`.
    You should also see that the log shows `master` and `local_branch` pointing
    to the same commit.

At this point your repo looks something like:
```
                           master
                           local_branch
                           HEAD
                             :
                             v
C0 <-- C1 <-- C2 <--- C4 <-- C6
       ^                     |
       +-- C5 <--------------+
```

Deleting branches
-----------------

In order to keep things tidy, you may wish to delete temporary branches:
```
git branch -d local_branch
```

Git is quite conservative here, and will not let you:

- Delete the branch that is currently checked out.

- Delete a branch that has un-merged commits.


Creating a feature branch
-------------------------

A common use of branches is to support work-in-progress, particularly
when a feature requires multiple commits to actually get it implemented,
debugged, and tested. These are often called "feature" branches, though
it is a convention rather than something enforced by git. Features
can be used to migrate partially completed work between repositories,
while always keeping the `master` branch in a compileable and tested
state.

Both you and your partner should pick some feature that you want
to implement, e.g. some function or program from the exercise.
Choose a feature name that makes sense, and is understandable: for
example, "C2_test_find_close_words" for part C2 from the first
exercise, or "B2_SentenceReader".

You should now each create a new local branch with that name:
```
$ git checkout master -b FEATURE_NAME
```
Ideally you would now implement this feature, using one or more
commits. However, for the lab purposes, you should just both
make some modification related to the feature and commit it locally.

Pushing a branch to a remote repo
--------------------------------

In the previous lab we set up various remotes which pointed at
the github repositories, such as `origin`. We can
push a local branch to a branch on a remote repository by explicitly specifying
a branch:
```
$ git push origin FEATURE_NAME
```

This will create a new branch FEATURE_NAME in the remote repository.

If you go to your repo in the github web-site, you should also be able to
select the branch from the "branches" drop-down on the left-hand side.

You should both push to the remote repo, so that both branches are
now visible in the github web-site.

Fetching branches from a remote repo
------------------------------------

We do not want to merge the features into `master` until they are complete and working correctly,
but we may wish to get access to the work-in-progress commits. To get the changes
from a repo _without_ merging them, we can use `git fetch`:
```
$ git fetch origin
```
This will retrieve the state of all branches, including any new branches which have
been created.

If you do `git branch` you will not see any new branches, as by default it only
shows local branches. However, you can tell it to show all the branches, including
remote branches, using the `-a` flag:
```
$ git branch -a
* master
  MY_FEATURE
  remotes/origin/MY_FEATURE
  remotes/origin/PARTNER_FEATURE
```
You can (if you wish) checkout the remote branch as expected:
```
$ git checkout PARTNER_FEATURE
```
It will automatically create a local branch called `PARTNER_FEATURE`, and synchronise
it with the remote feature.

You can also pull from a remote branch, merging changes straight into your
checked out copy:
```
$ git pull origin FEATURE_NAME
```
(Under the hood, `pull` is pretty much just a `fetch` followed by a `merge`).

Merging features back into master
---------------------------------

Now you have a feature branch, you should work on that feature
in order to implement it and get it working. It is worth doing
some actual work on the feature branches now, so that you both
have some changes to commit.


Eventually, after a sequence of commits, you will be happy with it,
and want to merge back to `master`. However, it is likely that `master` has
moved on by now. Imagine our history looks like this:
```
                   master
                     :
                     v
C0 <-- C1 <-- C2 <-- C3
       ^            
       |         
       +-- F1 <-- F2 <-- F3
                         ^
                         :
                       Feature
```
We are happy that commit F3 contains a complete working copy of the feature,
while commit C3 also passes all it's own tests.

Rather than merging `Feature` into `master`, it is better to merge `master`
into `Feature`, as it is possible that the act of merging breaks the functionality
added in one or the other.

So a reasonable process for merging is:

1.  Fetch all changes from the origin:
    ```
    $ git fetch origin
    ```

2.  Merge `master` into your local feature branch:
    ```
    $ git checkout FEATURE_NAME
    $ git merge master
    ```

3.  Test extensively to ensure that the merged branches perform correctly. Does
    everything still compile? Do the merged set of tests all pass?

4.  Fix anything that is broken. Commit the changes back to the FEATURE_NAME branch.

5.  Once you are happy, merge the changes locally:
    ```
    $ git checkout master
    $ git pull origin
    $ git merge FEATURE_NAME
    ```
    If all has gone well, there should be no conflicts, and local `master` and `FEATURE_NAME`
    both point at the same commit.

6.  Push back to origin:
    ```
    git push origin master
    ```

At this point the repository will look something like this:
```
                                     master
                                       :
                                       :
C0 <-- C1 <-- C2 <-- C3 <-----+        :
       ^                       \       :
       |                        v      v
       +-- F1 <-- F2 <-- F3 <-- F4 <-- F5
                                       ^
                                       :
                                     Feature
```
This assumes that F5 was an additional commit needed to fix some problems
occuring in the merge F4.

Putting it into practise
------------------------

The set of commands and concepts you now have should be sufficient to handle
almost any situation you find yourself in. The main ideas are:

- Keep master clean : ideally the `master` commit should always represent
  a compilable version of the code, where all test-cases pass. In practise
  this doesn't always happen, but it is good to aim for.

- Develop in branches : create features to represent work-in-progress. This
  is particularly useful if you aren't sure how easy/hard something is to
  implement, and allows you to maintain a few parallel streams of development.

- Commit frequently : if you are on a feature branch you can leave the
  repository in a an un-compilable state, so it is often useful to commit
  as you hit certain milestones: feature compiles; feature tests are added;
  feature passes tests.

- Push and fetch to move code : using git you can transfer partial work
  between repositories, allowing you to transfer works in progress
  between each other. This is particularly useful if one person gets
  stuck, or a feature turns out to be more time-consuming than expected.

The key commands you need are:

- `git add FILE` : Add a file to the repo.

- `git commit -a -m "MESSAGE"` : Commit all modified files.

- `git checkout BRANCH` : switch to the given branch.

- `git checkout HASH -b BRANCH` : create a branch based on the given hash, and check it out.

- `git push REMOTE BRANCH` : Push the current commit to a branch on a remote.

- `git pull REMOTE BRANCH` : Fetch changes from the branch _and_ merge them into the local repository.

- `git fetch REMOTE` : Fetch changes from the remote's branches, but do _not_ merge them.

- `git merge BRANCH` : Merge changes from the given branch into the local repo.

