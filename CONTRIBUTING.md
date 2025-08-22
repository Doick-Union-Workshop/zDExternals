# Contributing Guidelines

Thank you for contributing to this project!
To keep commit history clean and consistent, follow the [Conventional Commits](https://www.conventionalcommits.org/) specification.

## Commit Messages

Each commit message **must** follow this format:

```yml
<type>[optional scope]: <description>
```

- **type** – describes the category of change (see below)  
- **scope** – optional, specifies the part of the codebase (e.q. `externals` or `utils`)
- **description** – short summary in present tense, lowercase, no period at the end

## Commit Types

- **feat** – a new feature
- **fix** – a bug fix
- **docs** – documentation only changes (e.g. README, comments)
- **style** – formatting, whitespace, missing semicolons, etc. (no code changes)
- **refactor** – code change that neither fixes a bug nor adds a feature
- **perf** – performance improvement
- **build** – changes to the build system or external dependencies  
- **ci** – changes to CI/CD configuration files
- **chore** – other changes

## Examples

```yaml
✅ Correct:
feat: add helpers to set vob to floor
fix: resolve crash in Vob_SetToFloor external
docs: document Hlp_IsValidVob
refactor: simplify sky controller override
chore: bump version to 1.2.3
```

```yaml
❌ Incorrect:
Added new NPC check
Bugfix for menu
Docs update
````

## Additional Notes

- Use **English** in commit messages.  
- Keep descriptions concise (50 characters max).  
- If a commit closes an issue, use `Closes #123` in the commit body.
