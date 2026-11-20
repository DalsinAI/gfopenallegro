# Where allegro5/ came from

This tree is DalsinAI/amigaallegro at main, commit 823f17f78511c2ae85b93fd7060cc9fffc47d4af (7 Nov 2026), copied in on 20 Nov 2026 so that GFOpenAllegro is the one public home for our Allegro work.

amigaallegro is upstream Allegro 5.2.11.3 with our port on top:

- 51df076df: classic AmigaOS 3.x port foundation
- a55b4b2ea: OpenGPU bitmap presentation
- d30bac932: no OpenGL sync per bitmap batch at release
- 823f17f78: CI fixes

Its full history, including upstream Allegro's, stays in amigaallegro. Upstream's `.github/` workflows were left out, because they would not run from a subfolder.

amigaallegro also has an unmerged branch, `allegro4-cpu-bitmaps-20261102` (Allegro 4 APIs for Kraptor). allegro4/ here is the maintained Allegro 4. Fold anything that branch still adds into allegro4/, not into allegro5/.

Programs that pin an amigaallegro commit (Open Surge) keep working. Move them to a GFOpenAllegro commit when they are next updated.
