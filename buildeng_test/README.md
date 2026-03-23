# Build Engineer Take-Home Assessment

Welcome! This repository contains a take-home assessment for a Build Engineer candidate. Your objective is to complete the build pipeline using Buildbot and deliver a working `docker-compose` setup and associated files for evaluation.

## Objective

- Complete the Buildbot pipeline so that it compiles the provided C code, builds shared libraries, links them, and runs the resulting binary.
- The final binary, when run, will output a string. This string is your proof of a successful build.

## Repository Structure

- `docker/` — Dockerfiles, Buildbot configs, and supporting scripts. This is the important directory for you.
- `dev_src` — Main application source (Not meant to be read or modified.)
- `docker-compose.yml` — Orchestrates the Buildbot master and worker;
  feel free to modify if needed
- `README.md` — This file

## How to Build and Run

### 1. Build and Start the Pipeline

From the root of the repository, run:

```bash
docker-compose up -d --build
```

This will start both the Buildbot master and worker. The Buildbot web UI will be available at [http://localhost:8010](http://localhost:8010).

### 2. Trigger the Pipeline

- Open the Buildbot web UI: http://localhost:8010/#/builders/1
- Use the "force" scheduler to trigger a build of the `simple-pipeline`.
- The pipeline will:
  - Compile the shared libraries
  - Upload/download artifacts as needed
  - Link _and_ run the final binary. **You should check the output.**

### 3. Run the Binary Manually (if needed)

If you want to run the binary yourself after the pipeline completes:

```bash
LD_LIBRARY_PATH=. ./my_app
```

This ensures the dynamic linker can find the shared libraries in the current directory.

### 4. Output

When the build runs successfully, the "Run Program" stage will print a string to stdout. 

This is your proof of a successful build. Please send it back to us.

## Deliverables

- A **working** `master.cfg` (and all associated files needed to run the pipeline).
- The output string from the final binary.

NOTE: the master.cfg is the main "problem", and everything you need to fix the issue should be in this repository.

## Notes

- You may edit or add files as needed to complete the pipeline.
- Please ensure your solution works from a clean checkout and fresh Docker build.

Good luck!
